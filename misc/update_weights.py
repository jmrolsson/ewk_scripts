#! /usr/bin/env python
#
# @file:    update_weights.py
# @purpose: update 'num events' entry in JSON dictionary of weights
# @author:  Joakim Olsson <joakim.olsson@cern.ch>
# @date:    September 2017
#
from __future__ import print_function

# Logging
import logging
FORMAT = "[%(asctime)s][%(levelname)s]  %(message)s (%(filename)s:%(lineno)d)"
logging.basicConfig(format=FORMAT)
logger = logging.getLogger("update_weights")

# Other imports
import glob
import argparse
import json
import re
import io
import sys

try:
  import ROOT
except ImportError:
  logger.error('Please set up ROOT (and PyROOT bindings) before continuing')
  sys.exit(1)
from ROOT import TFile

did_regex = re.compile('\.(?:00)?(\d{6})\.')
def get_did(filename):
  global logger
  global did_regex
  m = did_regex.search(filename)
  if m is None:
    logger.warning('Can\'t figure out the DID! Using input filename: {0}'.format(filename))
    return filename.split('/')[-1]
  return m.group(1)

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='grab cutflows from root files')
    parser.add_argument('file_paths', metavar='<file_paths>', type=str, help='Input file pattern. Example: \'./my_path/*.root\'')
    parser.add_argument('--cutflow-bin', dest='cutflow_bin', type=int, required=False, help='Cutflow bin to read', default=2)
    parser.add_argument('--weights', metavar='<weights.json>', type=str, help='JSON dictionary of weights', default = 'weights.json')
    parser.add_argument('--threshold', type=float, help='Threshold for number comparison', default = 0.001)
    parser.add_argument('-o', '--output', dest='output_file', metavar='<weights_modified.json>', type=str, help='Updated JSON dictionary of weights.', default = 'weights_modified.json')
    parser.add_argument('-v', '--verbose', dest='verbose', action='count', default=0, help='Enable verbose output of various levels. Default: no verbosity')
    args = parser.parse_args()

    # set verbosity for python printing
    if args.verbose < 2:
        logger.setLevel(20 - args.verbose*10)
    else:
        logger.setLevel(logging.NOTSET + 1)

    # get the weights configurations for scaling
    try:
        weights = json.load(file(args.weights))

        file_paths = glob.glob(args.file_paths)
        logger.info('Begin processing files...')
        for f in file_paths:
            logger.debug('Input file:\n '+f)
            did = get_did(f)
            if did in weights:
              logger.debug('DID {} found in {}'.format(did, args.weights))
              logger.debug('Dictionary entry for DID {}: {}'.format(did, weights[did]))
            else:
              logger.warning('DID {} not found in {}'.format(did, args.weights))
              continue

            root_file = TFile.Open(f, 'READ')
            nevt_dict = weights[did]['num events']
            nevt_actual = root_file.Get('cut_flow').GetBinContent(2)
            logger.debug('num events in weights dictionary: {}'.format(nevt_dict))
            logger.debug('actual num events in dataset root file: {}'.format(nevt_actual))
            if (abs(float(nevt_actual)/float(nevt_dict) - 1.000) > args.threshold):
                logger.debug('--> Mismatch between weights dictionary and actual number of events, updating dictionary for DID: {}'.format(did))
                logger.info('({}) \'num events\': {} -> {}, ratio: {}'.format(did, nevt_dict, nevt_actual, nevt_actual/nevt_dict))
                weights[did]['num events'] = nevt_actual

        # write JSON
        try:
          to_unicode = unicode
        except NameError:
          to_unicode = str
        with io.open(args.output_file, 'w', encoding='utf8') as f_json:
            f_json.write(to_unicode(json.dumps(weights, indent=2, sort_keys=True,  separators=(',', ': '), ensure_ascii=False)))
            logger.info('Saved updated weights dictionary to: {}'.format(args.output_file))

        logger.info('Done!')

    except IOError:
        logger.error('No weights file found named \'{0:s}\' (specify by \'--weights <weights.json>\')'.format(args.weights))
        sys.exit(1)
