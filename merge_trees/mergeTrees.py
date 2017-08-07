#!/usr/bin/env python
# -*- coding: utf-8 -*-,
# @file:    mergeTrees.py
# @purpose: merge many files into few files and copy trees and systematics
# @author:  Giordon Stark <gstark@cern.ch>
# @date:    July 2016
#

# __future__ imports must occur at beginning of file
# redirect python output using the newer print function with file description
#   print(string, f=fd)
from __future__ import print_function
import logging

BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE = range(8)
#The background is set with 40 plus the number of the color, and the foreground with 30
#These are the sequences need to get colored ouput
RESET_SEQ = "\033[0m"
COLOR_SEQ = "\033[1;%dm"
BOLD_SEQ = "\033[1m"

def formatter_message(message, use_color = True):
  if use_color:
    message = message.replace("$RESET", RESET_SEQ).replace("$BOLD", BOLD_SEQ)
  else:
    message = message.replace("$RESET", "").replace("$BOLD", "")
  return message

COLORS = {
  'WARNING': YELLOW,
  'INFO': WHITE,
  'DEBUG': BLUE,
  'CRITICAL': YELLOW,
  'ERROR': RED
}

class ColoredFormatter(logging.Formatter):
  def __init__(self, msg, use_color = True):
    logging.Formatter.__init__(self, msg)
    self.use_color = use_color

  def format(self, record):
    levelname = record.levelname
    if self.use_color and levelname in COLORS:
      levelname_color = COLOR_SEQ % (30 + COLORS[levelname]) + levelname + RESET_SEQ
      record.levelname = levelname_color
    return logging.Formatter.format(self, record)

# Custom logger class with multiple destinations
class ColoredLogger(logging.Logger):
  FORMAT = "[$BOLD%(asctime)s$RESET][%(levelname)-18s]  %(message)s ($BOLD%(filename)s$RESET:%(lineno)d)"
  #FORMAT = "[$BOLD%(name)-20s$RESET][%(levelname)-18s]  %(message)s ($BOLD%(filename)s$RESET:%(lineno)d)"
  COLOR_FORMAT = formatter_message(FORMAT, True)
  def __init__(self, name):
    logging.Logger.__init__(self, name, logging.DEBUG)
    color_formatter = ColoredFormatter(self.COLOR_FORMAT)
    console = logging.StreamHandler()
    console.setFormatter(color_formatter)
    self.addHandler(console)
    return

root_logger = logging.getLogger()
root_logger.setLevel(logging.NOTSET)
logging.setLoggerClass(ColoredLogger)
logger = logging.getLogger("mergeTrees")

# import the rest of the stuff
import argparse
import os
import subprocess
import sys
from random import choice
import tempfile
from array import array
import re
import json

try:
  import ROOT
except ImportError:
  logger.exception('Please set up ROOT (and PyROOT bindings) before continuing')
  sys.exit(1)

did_regex = re.compile('\.(?:00)?(\d{6})\.')
def get_did(filename):
  global did_regex
  global logger
  m = did_regex.search(filename)
  if m is None:
    logger.warning('Can\'t figure out the DID! Using input filename: {0}'.format(filename))
    return filename.split("/")[-1]
  return m.group(1)

def get_scaleFactor(did, weights):
  global logger
  weight = weights[did]
  logger.debug("Weights for {0:s}".format(did))
  logger.debug("\t {0:s}".format(str(weight)))
  scaleFactor = 1.0
  cutflow = weight.get('num events', 0)
  if cutflow == 0:
    logger.error("Num. events = 0 for {0:s}".format(did))
  scaleFactor /= cutflow
  logger.debug("___________________________________________________________________")
  logger.debug(" {0:8s} Type of Scaling Applied       |        Scale Factor      ".format(did))
  logger.debug("========================================|==========================")
  logger.debug("Cutflow:           {0:20.10f} | {1:0.10f}".format(cutflow, scaleFactor))
  scaleFactor *= weight.get('cross section')
  logger.debug("Cross Section:     {0:20.10f} | {1:0.10f}".format(weight.get('cross section'), scaleFactor))
  scaleFactor *= weight.get('filter efficiency')
  logger.debug("Filter Efficiency: {0:20.10f} | {1:0.10f}".format(weight.get('filter efficiency'), scaleFactor))
  scaleFactor *= weight.get('k-factor')
  logger.debug("k-factor:          {0:20.10f} | {1:0.10f}".format(weight.get('k-factor'), scaleFactor))
  logger.debug( "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾")
  return scaleFactor

def add_sampleWeight_branch(did, weights, tree, branchname='weight_lumi'):
  scaleFactor = get_scaleFactor(did, weights)
  branch_val = array( 'f', [ scaleFactor ] )
  branch_val_up = array( 'f', [ scaleFactor*(1+weights[did].get('rel uncert', -1.0)) ] )
  branch_val_down = array( 'f', [ scaleFactor*(1-weights[did].get('rel uncert', 1.0)) ] )
  branches = []
  branches.append(tree.Branch('{0:s}'.format(branchname), branch_val, '{0:s}/F'.format(branchname)))
  branches.append(tree.Branch('{0:s}_up'.format(branchname), branch_val_up, '{0:s}_up/F'.format(branchname)))
  branches.append(tree.Branch('{0:s}_down'.format(branchname), branch_val_down, '{0:s}_down/F'.format(branchname)))
  for i in range(tree.GetEntries()):
    tree.GetEntry(i)
    for b in branches:
      b.Fill()

  #tree.Fill()

if __name__ == "__main__":

  # if we want multiple custom formatters, use inheriting
  class CustomFormatter(argparse.ArgumentDefaultsHelpFormatter):
    pass

  # __version__ = subprocess.check_output(["git", "describe", "--always"], cwd=os.path.dirname(os.path.realpath(__file__))).strip()

  parser = argparse.ArgumentParser(description='Determine if a sample has MC Weight issues',
                                   usage='\033[93m%(prog)s\033[0m files [options]',
                                   formatter_class=lambda prog: CustomFormatter(prog, max_help_position=30))
  parser.add_argument('files', type=str, nargs='+', help='HistFitter outputs from MBJ code')

  parser.add_argument('--filters', metavar='filters.json', type=str, help='JSON dictionary where key=DID and val=selection to apply')
  parser.add_argument('--weights', metavar='weights.json', type=str, help='JSON dictionary of weights Can be http:// url or local file!')
  parser.add_argument('--did-to-group', metavar='did_to_group.json', type=str, help='JSON dictionary mapping DID to group. Can be http:// url or local file!')

  parser.add_argument('--trees', metavar='tree', type=str, nargs='+', help='TTrees to merge and copy over in signal and bkgd files',
                      default=['nominal',
                               'JET_GroupedNP_1__1up',
                               'JET_GroupedNP_1__1down',
                               'JET_GroupedNP_2__1up',
                               'JET_GroupedNP_2__1down',
                               'JET_GroupedNP_3__1up',
                               'JET_GroupedNP_3__1down',
                               'JET_JER_SINGLE_NP__1up',
                               'JET_EtaIntercalibration_NonClosure__1up'])
  """
                               'JET_JMS_GroupedNP_1__1up',
                               'JET_JMS_GroupedNP_1__1down'])
                               'EG_RESOLUTION_ALL__1down',
                               'EG_RESOLUTION_ALL__1up',
                               'EG_SCALE_ALL__1down',
                               'EG_SCALE_ALL__1up',
                               'MET_SoftTrk_ResoPara',
                               'MET_SoftTrk_ResoPerp',
                               'MET_SoftTrk_ScaleDown',
                               'MET_SoftTrk_ScaleUp',
                               'MUONS_ID__1down',
                               'MUONS_ID__1up',
                               'MUONS_MS__1down',
                               'MUONS_MS__1up',
                               'MUONS_SCALE__1down',
                               'MUONS_SCALE__1up"*/
  """

  parser.add_argument('--dids', metavar='did', type=str, nargs='+', help='DIDs to use or not use (see --blacklist-dids)', default=[])
  parser.add_argument('--blacklist-dids', action='store_true', help='If enabled, the specified DIDs will be skipped')

  parser.add_argument('--groups-bkg', metavar='group', type=str, nargs='+', help='Groups of bkgd to merge',
                      default=['ttbar',
                               'singletop',
                               'diboson',
                               'topEW',
                               'W_sherpa',
                               'Z_sherpa'])
  parser.add_argument('--groups-sig', metavar='group', type=str, nargs='+', help='Groups of signal to collect but not merge', default=['Gtt', 'Gbb'])

  parser.add_argument('--output-suffix', metavar='tag#####', type=str, default='', help='Add a suffix to output files, perhaps to specify a nominal only: --output-suffix _nominal')

  parser.add_argument('--do-data', action='store_true', help='Process and merge data files. Otherwise, skip this process.')

  parser.add_argument('--do-jms-fix', action='store_true', help='Add JMS systematic branches according to the prescription in this code.')

  parser.add_argument('--do-backward-compatibility', action='store_true', help='Rename the branch names to get things backgwards-compatible. See the code for what this entails.')

  parser.add_argument('-v', '--verbose', dest='verbose', action='count', default=0, help='Enable verbose output of various levels. Default: no verbosity')
  # parser.add_argument('--version', action='version', version='\033[93m%(prog)s\033[0m \033[94m{version}\033[0m'.format(version=__version__), default='\033[94m{version}\033[0m'.format(version=__version__))

  args = parser.parse_args()

  # set verbosity for python printing
  if args.verbose < 2:
    logger.setLevel(20 - args.verbose*10)
  else:
    logger.setLevel(logging.NOTSET + 1)

  """
    Load the files in -- do not necessarily need a filter
  """
  try:
    filters = json.load(file(args.filters))
  except IOError:
    logger.warning("No filter file. Is this expected? You gave me '{0:s}'".format(args.filters))
    filters = {}

  # if args.weights.startswith('http'):
  #   import requests
  #   weights = json.load(requests.get(args.weights).text)
  # else:
  weights = json.load(file(args.weights))

  # if args.did_to_group.startswith('http'):
  #   import requests
  #   did_to_group = json.load(requests.get(args.did_to_group).text)
  # else:
  did_to_group = json.load(file(args.did_to_group))


  """
    Next, ensure we have information on all DIDs used in the files.
  """
  checkedDIDs = []
  for f in args.files:
    # skip data
    if '.data.' in f: continue
    did = get_did(f)
    if did in checkedDIDs: continue
    # whitelist or blacklist
    if bool(did in args.dids) == bool(args.blacklist_dids): continue
    checkedDIDs.append(did)

    logger.info("Checking {0:s}".format(did))
    if did in did_to_group:
      logger.info("\t has group {0:s}".format(did_to_group[did]))
    else:
      logger.error("\t does not have a group assigned")
      sys.exit(1)
    # skip any dids that are not in groups we care about for bkg or signal
    group = did_to_group[did]
    if group not in args.groups_bkg and not any(g in group for g in args.groups_sig if g): continue

    # check that the DIDs we are looking at have weights
    if did in weights:
      logger.info("\t has weight")
    else:
      logger.error("\t does not have weight")
      sys.exit(1)

    logger.info("\t has filter: {0:s}".format(str(did in filters)))

  # signal is fuzzy-matched, bkg is exact-matched
  all_groups = [group for group in (args.groups_bkg + args.groups_sig) if group]
  # check the groups and see if we have splitting information
  for group in all_groups:
    logger.info("Checking {0:s}".format(group))
    logger.info("\t has defined splits: {0:s}".format(str(any(group in name for name in filters.keys()))))
    for name in filters.keys():
      if group not in name: continue
      selection = filters[name]
      logger.info("\t\t {0:s} \t {1:s}".format(name, selection))

  """
    In this section,
      - we read in all the data files (must have 'data' in the name)
      - create a TChain of the 'nominal' branch
      - create an output file for data
      - clone the TChain as a TTree which gets saved to the output
      - close the output file

    TODO: Add protection if output file already exists.
  """
  data_files = [f for f in args.files if '.data.' in f or '.data_' in f]
  if args.do_data and len(data_files) > 0:
    logger.info("Doing the data files")
    tc = ROOT.TChain('nominal')
    for f in data_files:
      logger.debug('\t{0:s}'.format(f))
      tc.Add(f)
    logger.info('Creating output file {0:s}{1:s}.root'.format('Data', args.output_suffix))
    output_file = ROOT.TFile('Data{0:s}.root'.format(args.output_suffix), 'UPDATE')
    output_file.cd()
    #tree = tc.CopyTree('')
    tree = tc.CloneTree(-1, "fast")
    tree.SetName("Data")
    tree.SetTitle("Data")
    tree.SetAlias("MJSum_rc_r08pt10_nominal","MJSum_rc_r08pt10")
    #tree.SetDirectory(output_file)
    #output_file.cd()
    #tree.Write()
    output_file.Write("",ROOT.TObject.kOverwrite)
    output_file.Close()
    logger.info('Finished creating output file')

  """
    In this section,
      - we read in all the bkg files
      - sort everything / filter by group
      - make temporary files for things that need hadding or filtering
      - for each group
        - create the output file
        - for each branch
          - create a TChain
          - apply selection if desired (TChain::CopyTree)
          - clone the TChain as a TTree which gets saved to the output
          - apply weights by making a new branch
       - clean up temporary files

    TODO: Add protection if output file already exists
  """
  files_by_did = {}
  # first group by did to figure out if we need to merge files together or not
  for f in args.files:
    if f in data_files: continue
    did = get_did(f)
    # whitelist or blacklist
    if bool(did in args.dids) == bool(args.blacklist_dids): continue
    if did in files_by_did:
      files_by_did[did].append(f)
    else:
      files_by_did[did] = [f]

  # here, we need to do some temporary TChains and copy the trees we want
  tmpDir = tempfile.mkdtemp(dir=os.getcwd())
  logger.info("Temporary directory created: {0:s}".format(tmpDir))

  # make a dictionary mapping the group to the files inside the group
  files_by_group = {}
  for did,files in files_by_did.iteritems():
    group = did_to_group[did]
    # skip any dids that are not in groups we care about for bkg or signal
    if group not in args.groups_bkg and not any(g in group for g in args.groups_sig if g): continue
    logger.debug("Working on {0:s} which has {1:d} files".format(did, len(files)))
    logger.debug("\t belongs to group {0:s}".format(group))

    """
      always make a temporary file since we need to do at least one of the following
      which is sorted from most likely to least likely
        - add a new branch for sample weight (weight_lumi)
        - merge multiple files of the same DID together
        - apply a selection/filter to the ttrees
    """
    logger.debug("Making a tmp file for {0:s} with {1:d} files".format(did, len(files)))
    # wrap this portion in a try statement because we need to make sure we clean up after ourselves
    try:
      tmpFile = os.path.join(tmpDir, '{0:s}.root'.format(did))
      logger.debug("Creating temporary file: {0:s}".format(tmpFile))
      for treename in args.trees:
        # start making the tchain
        logger.debug("\tBuilding a TChain for {0:s}".format(treename))
        tc = ROOT.TChain(treename)
        for f in files:
          tc.Add(f)
        logger.info("{0:s}/{1:s} has {2:d} entries".format(did, treename, tc.GetEntries()))
        # apply a selection/filter if defined
        # open the file to update it
        output_file = ROOT.TFile.Open(tmpFile, 'UPDATE')
        output_file.cd()
        if did in filters or '*' in filters: logger.debug("\tApplying filter: {0:s}".format(filters.get(did, filters.get('*'))))
        copy_tree = False
        while not copy_tree:
          copy_tree = tc.CopyTree(filters.get(did, filters.get('*', '')))
        if did in filters: logger.info("{0:s}/{1:s} has {2:d} entries after filter".format(did, treename, copy_tree.GetEntries()))
        logger.debug("\tAdding the sample weight for {0:s} to the tree".format(did))
        add_sampleWeight_branch(did, weights, copy_tree)
        logger.debug("\tSetting an alias for the MJSum branch")
        copy_tree.SetAlias("MJSum_rc_r08pt10_nominal","MJSum_rc_r08pt10")
        logger.debug("\tWriting to {0:s}".format(tmpFile))
        output_file.Write("",ROOT.TObject.kOverwrite)
        output_file.Close()

        if args.do_jms_fix and treename == 'nominal':
          logger.debug("\tDoing the JMS fix")
          for systname in ['JET_JMS_GroupedNP_1__1up','JET_JMS_GroupedNP_1__1down']:
            output_file = ROOT.TFile.Open(tmpFile, 'UPDATE')
            output_file.cd()
            tree = output_file.Get(treename)
            logger.debug("\t\t{0:s} is being cloned".format(systname))
            syst_tree = tree.CloneTree(-1, "fast")
            syst_tree.SetName(systname)
            syst_tree.SetTitle(systname)
            if systname == 'JET_JMS_GroupedNP_1__1up':
              syst_tree.SetAlias("MJSum_rc_r08pt10_nominal","MJSum_rc_r08pt10_JMSUP")
            elif systname == 'JET_JMS_GroupedNP_1__1down':
              syst_tree.SetAlias("MJSum_rc_r08pt10_nominal", "MJSum_rc_r08pt10_JMSDOWN")
            output_file.Write("",ROOT.TObject.kOverwrite)
            output_file.Close()

      try:
        files_by_group[group].append(tmpFile)
      except KeyError:
        files_by_group[group] = [tmpFile]
    except:
      # clean up after ourselves
      import shutil
      shutil.rmtree(tmpDir, ignore_errors=True)
      raise

  # JMS fix requires adding the two new TTrees in our loop and copying them from nominal
  if args.do_jms_fix:
    args.trees.extend(['JET_JMS_GroupedNP_1__1up','JET_JMS_GroupedNP_1__1down'])

  signal_filename = 'Sig{0:s}.root'.format(args.output_suffix)
  logger.info('Signal output file {0:s}'.format(signal_filename))
  bkg_filename = 'Bkg{0:s}.root'.format(args.output_suffix)
  logger.info('Background output file {0:s}'.format(bkg_filename))
  # create the output files for signal and background

  # this contains the output file that the given group is being written to
  output_file = None
  for group, files in files_by_group.iteritems():
    if group in args.groups_bkg:
      logger.debug('Group {0:s} is identified as BACKGROUND'.format(group))
      output_filename = bkg_filename
    else:
      logger.debug('Group {0:s} is identified as SIGNAL'.format(group))
      output_filename = signal_filename

    logger.info('\tGroup {0:s} will be written to {1:s}'.format(group, output_filename))
    # loop over the trees we need to make
    for treename in args.trees:
      logger.debug('\tBuilding TChain for {0:s}'.format(treename))
      tc = ROOT.TChain(treename)
      for f in files:
        logger.debug('\t\t{0:s}'.format(f))
        tc.Add(f)
      # open the file
      output_file = ROOT.TFile(output_filename, 'UPDATE')
      output_file.cd()
      logger.debug('\tCloning TChain now')
      tree = tc.CloneTree(-1, "fast")

      out_group = group
      out_treename = treename
      if args.do_backward_compatibility:
        out_group = out_group.replace('singletop', 'SingleTop')
        out_group = out_group.replace('topEW', 'TopEW')
        out_group = out_group.replace('_sherpa', 'jets')
        out_group = out_group.replace('_5000', '')
        out_treename = treename.replace('nominal', 'NoSys')
      # names need to be format <sample>_<systematic>
      tree.SetName("_".join([out_group, out_treename]))
      tree.SetTitle("_".join([out_group, out_treename]))
      output_file.Write("",ROOT.TObject.kOverwrite)
      output_file.Close()
      logger.info('\tTree {0:s} was written to file'.format("_".join([out_group, out_treename])))

      output_file = ROOT.TFile(output_filename, 'UPDATE')
      output_file.cd()
      tree = output_file.Get("_".join([out_group, out_treename]))
      # check if we need to do some splitting
      for name,selection in filters.get(group, []):
        logger.info('\tApplying filter {0:s} with selection {1:s}'.format(name, selection))
        copy_tree = tree.CopyTree(selection)
        # we're technically creating a new sample called <sample>_<name of selection>
        copy_tree.SetName("_".join([out_group, name, out_treename]))
        copy_tree.SetTitle("_".join([out_group, name, out_treename]))
        #copy_tree.Write()
        logger.info('\t\tTree {0:s} was written to file'.format("_".join([out_group, name, out_treename])))
      output_file.Write("",ROOT.TObject.kOverwrite)
      output_file.Close()

  import shutil
  shutil.rmtree(tmpDir, ignore_errors=True)

  logger.info("Don't forget to remove the temp directory {0:s}".format(tmpDir))
  logger.info("Completely finished! Enjoy.")
