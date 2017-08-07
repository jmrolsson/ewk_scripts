#! /usr/bin/env python
from __future__ import print_function
import os
import re
import glob
import subprocess

import argparse
parser = argparse.ArgumentParser(description="Make flat ntuples from MBJ tree output files (Author: Joakim Olsson <joakim.olsson@cern.ch>)")

parser.add_argument('top_level', metavar='<directory>', type=str, help='Top-Level directory containing files. Example: "tree/"')
parser.add_argument('file_pattern', metavar='<file pattern>', type=str, help='File patterns of files to process. Example: "*.root"')

# parse the arguments, throw errors if missing any
args = parser.parse_args()

paths = glob.glob(args.top_level)

for path in paths:

    files = glob.glob(os.path.join(path, args.file_pattern))
    i = 0
    nfiles = len(files)
    while files:
        input_file = files.pop(0)
        output_file = input_file+".flattened"
        treename = 'nominal'
        print("Processing file {}/{}".format(i, nfiles))
        print("Input file: {}".format(input_file))
        print("Output file: {}".format(output_file))
        i += 1

        cmd = "./run_mbj_flatten_tree {} {} {}".format(
            treename, input_file, output_file)
        subprocess.call([cmd], shell=True)

print("All done. YAY!")
