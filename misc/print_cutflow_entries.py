#! /usr/bin/env python
from __future__ import print_function
from ROOT import TFile
import glob
import argparse

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='grab cutflows from root files')
    parser.add_argument('file_paths', metavar='<file_paths>', type=str, help='Input file pattern. Example: "./my_path/*.root"')
    parser.add_argument('--cutflow-max-bin', dest='cutflow_max_bin', type=int, required=False, help='Max cutflow bin to print.', default=3)
    args = parser.parse_args()

          # get the weights configurations for scaling
          weights = {}
          if args.weights_file:
              weights = json.load(file(args.weights_file))

    file_paths = glob.glob(args.file_paths)
    for file_path in file_paths:
        print('\n'+file_path)
        root_file = TFile.Open(file_path, 'READ')
        cutflow = root_file.Get("cut_flow")
        for i in xrange(1, args.cutflow_max_bin):
            if i > cutflow.GetNbinsX(): continue
            print(cutflow.GetBinContent(i))
