#!/usr/bin/env python
# @file:    apply_filters_to_dids.py
# @purpose: apply filters to individual datasets based in dids (re-using code from Giordon Stark's <gstark@cern.ch> mergeTrees.py script)
# @author:  Joakim Olsson <joakim.olsson@cern.ch>
# @date:    July 2017
#

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
logger = logging.getLogger("apply_filters_to_dids")

import argparse
import os
import subprocess
import sys
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

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Apply filters to individual dids')

    parser.add_argument('files', type=str, nargs='+', help='HistFitter outputs from MBJ code')
    parser.add_argument('--filters', metavar='filters.json', type=str, help='JSON dictionary where key=DID and val=selection to apply')
    parser.add_argument('--output-suffix', metavar='tag#####', type=str, default='.root', help='Add a suffix to output files, perhaps to specify the type of filter applied --output-suffix _ht')
    parser.add_argument('--trees', metavar='tree', type=str, nargs='+', help='TTrees to merge and copy over in signal and bkgd files', default=['nominal'])
    parser.add_argument('--dids', metavar='did', type=str, nargs='+', help='DIDs to use or not use (see --blacklist-dids)', default=[])
    parser.add_argument('-o', '--output', required=False, type=str, dest='output_directory', metavar='<directory>', help='output directory to store the filtered files', default='filtered_dids')
    parser.add_argument('-v', '--verbose', dest='verbose', action='count', default=0, help='Enable verbose output of various levels. Default: no verbosity')

    args = parser.parse_args()

    # set verbosity for python printing
    if args.verbose < 2:
        logger.setLevel(20 - args.verbose*10)
    else:
        logger.setLevel(logging.NOTSET + 1)

    # load filters
    try:
      filters = json.load(file(args.filters))
    except IOError:
      logger.error("No filter file found for '{0:s}'. A valid filter file is required.".format(args.filters))
      sys.exit(1)

    # ensure output dir exists
    if not os.path.exists(args.output_directory):
        os.makedirs(args.output_directory)

    # organize input files based on dataset id
    datasets = {}
    for f in args.files:
        # skip data
        if '.data.' in f: continue
        # check if did is to be processed
        did = get_did(f)
        if did not in args.dids: continue
        if did in datasets:
            datasets[did].append(f)
        else:
            datasets[did] = [f]

    # apply filters, output one file per dataset id
    for did, files in datasets.iteritems():
        output_filename = os.path.join(args.output_directory, "{0:s}{1:s}".format(did, args.output_suffix))
        logger.info('Creating output file {0:s}'.format(output_filename))
        output_file = ROOT.TFile(output_filename, 'RECREATE')
        output_file.cd()

        for tree_name in args.trees:
            tc = ROOT.TChain(tree_name)
            logger.debug('Creating TChain {0:s}'.format(tree_name))
            for f in files:
                logger.debug('Adding file {0:s}'.format(f))
                tc.Add(f)
            logger.info('Copying tree {0:s}'.format(tree_name))
            copy_tree = tc.CopyTree(filters.get(did, filters.get('*', '')))
        output_file.Write("", ROOT.TObject.kOverwrite)
        output_file.Close()
