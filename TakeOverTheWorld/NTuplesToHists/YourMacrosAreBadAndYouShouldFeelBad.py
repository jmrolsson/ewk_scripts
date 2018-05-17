import json
import ROOT
import os
import sys

from rootpy.io import root_open
from rootpy.plotting import Hist, Hist2D, Hist3D
from rootpy.plotting import set_style
from rootpy.tree import Tree, TreeChain
import numpy as np
import re

import argparse

ROOT.gROOT.SetBatch(True)

def ensure_dir(f):
    d = os.path.dirname(f)
    if not os.path.exists(d):
        os.makedirs(d)

parser = argparse.ArgumentParser(description='Author: G. Stark')
parser.add_argument('files', type=str, nargs='+', metavar='<file.root>', help='ROOT files containing the jigsaw information. Histograms will be drawn and saved in the file.')
parser.add_argument('--config', required=True, type=str, dest='config', metavar='<file.json>', help='json file containing configurations for making histograms')
parser.add_argument('--out_tdirectory', required=False, type=str, dest='outdir', metavar='', help='TDirectory to store all generated histograms', default='all')
parser.add_argument('--treename', required=False, type=str, dest='treename', metavar='', help='Tree containing the ntuple information', default='oTree')
parser.add_argument('--filters', required=False, type=str, help='JSON dictionary where key=DID and val=selection to apply', default='filters.json')
parser.add_argument('--eventWeight', required=False, type=str, dest='eventWeightBranch', metavar='', help='Event Weight Branch name', default='weight')
parser.add_argument('--newOutputs', action='store_true', default=False, help='create new output files for histograms')
parser.add_argument('--doNotOverwrite', action='store_true', default=False, help='skip existing .hists files')
parser.add_argument('--copyHists', type=str, required=False, nargs='+', dest='hists', metavar='<histname>', help='List of histograms to copy (if any) from the input file')
parser.add_argument('--copyMBJCutflow', action='store_true', dest='copy_mbj_cutflow', default=False, help='Copy the master cutflow named "cut_flow" used in MBJ')
parser.add_argument('--doData', action='store_true', dest='do_data', default=False, help='If running on data')
parser.add_argument('--doDataPRW', action='store_true', default=False, help='Apply pileup reweighting scale factor to data')
parser.add_argument('-o', required=False, type=str, dest='output_folder', metavar='', help='Specify folder where to store output files', default='')

# parse the arguments, throw errors if missing any
args = parser.parse_args()

try:
  config = json.load(file(args.config))
except IOError:
  print "A config file is required! Couldn't open '{0:s}'".format(args.config)
  sys.exit(1)

try:
  filters = json.load(file(args.filters))
except IOError:
  # print "No filter file. Is this expected? You gave me '{0:s}'".format(args.filters)
  filters = {}

did_regex = re.compile("(?<=\.)\d{6}(?=\.)")

for f in args.files:
  print "opening {0}".format(f)
  gen_filt = None
  if did_regex.search(f):
    did = did_regex.search(f).group()
    if did in filters or '*' in filters:
      gen_filt = filters.get(did, filters.get('*'))
  if args.newOutputs:
    in_file = root_open(f, "READ")
    out_file_path = f+".hists"
    if args.output_folder != '':
      ensure_dir(args.output_folder)
      out_file_path = os.path.join(args.output_folder, os.path.basename(f)+".hists")
    if (args.doNotOverwrite and os.path.isfile(out_file_path)): continue
    out_file = root_open(out_file_path, "RECREATE")
    tree = in_file.get(args.treename)
    if (args.hists != None and len(args.hists)>0):
     out_file.cd()
     for hist in args.hists:
       in_file.Get(hist).Write()
    if args.copy_mbj_cutflow:
      cf = in_file.Get('cut_flow')
      cf2 = Hist(1, 0, 1, name='cutflow')
      cf2.Sumw2()
      cf2.SetEntries(cf.GetBinContent(1))
      cf2.SetBinContent(1, cf.GetBinContent(2))
      cf2.SetBinError(1, np.sqrt(cf.GetBinContent(1))*cf.GetBinContent(2)/cf.GetBinContent(1))
      allDir = os.path.join(args.outdir, 'all')
      out_file.mkdir(allDir, recurse=True)
      try: out_file.cd(allDir)
      except: pass
      cf2.Write()

  else:
    out_file = root_open(f, "UPDATE")
    tree = out_file.get(args.treename)
  # create tdirectory and cd into it
  print "\tmaking tdirectory {0}".format(args.outdir)


  # for each thing to draw, we want to apply a selection on them too
  for cut in config['cuts']:
    innerDir = os.path.join(args.outdir, cut['name'])
    if not args.copy_mbj_cutflow:
      try: out_file.rmdir(innerDir)
      except: pass
      try: out_file.rm(innerDir)
      except: pass
    try: out_file.mkdir(innerDir, recurse=True)
    except: pass
    try: out_file.cd(innerDir)
    except: pass
    # get list of things to draw
    for toDraw in config['draw']:
      histName = toDraw['name']

      histDimension = len(toDraw['draw'].split(':'))
      print "\tmaking {4}D histogram {0}\n\t{1} bins from {2} to {3}".format(toDraw['name'], toDraw['nbins'], toDraw['min'], toDraw['max'], histDimension)

      if histDimension == 1:
        h = Hist(toDraw['nbins'], toDraw['min'], toDraw['max'], name=histName)
      elif histDimension == 2:
        h = Hist2D(toDraw['nbins'][0], toDraw['min'][0], toDraw['max'][0],
                   toDraw['nbins'][1], toDraw['min'][1], toDraw['max'][1], name=histName)
      elif histDimension == 3:
        h = Hist2D(toDraw['nbins'][0], toDraw['min'][0], toDraw['max'][0],
                   toDraw['nbins'][1], toDraw['min'][1], toDraw['max'][1],
                   toDraw['nbins'][2], toDraw['min'][2], toDraw['max'][2], name=histName)
      else:
        raise ValueError('I dunno how to handle {0}'.format(toDraw))

      # things look ok, so we draw to the histogram
      if args.do_data:
        if args.doDataPRW and 'average_int_per_crossing' in toDraw['draw']:
          print "\t\tdrawing {0}\n\t\twith cut ({1})".format(toDraw['draw']+"*1.0/1.09", cut['name'])
          tree.Draw(toDraw['draw']+"*1.0/1.09", '({0:s})'.format(cut['cut']), hist=h)
        else:
          print "\t\tdrawing {0}\n\t\twith cut ({1})".format(toDraw['draw'], cut['name'])
          tree.Draw(toDraw['draw'], '({0:s})'.format(cut['cut']), hist=h)
      elif gen_filt:
        print "\t\tdrawing {0}\n\t\twith cut ({1})*({2})*({3})".format(toDraw['draw'], args.eventWeightBranch, cut['name'], gen_filt)
        tree.Draw(toDraw['draw'], '({0:s})*({1:s})*({2:s})'.format(args.eventWeightBranch, cut['cut'], gen_filt), hist=h)
      else:
        print "\t\tdrawing {0}\n\t\twith cut ({1})*({2})".format(toDraw['draw'], args.eventWeightBranch, cut['name'])
        tree.Draw(toDraw['draw'], '({0:s})*({1:s})'.format(args.eventWeightBranch, cut['cut']), hist=h)
      # write to file
      print "\t\twriting to file"
      h.write()
  out_file.close()
