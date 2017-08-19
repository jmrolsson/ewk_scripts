import os
import re
import numpy as np

if __name__ == '__main__':

  import argparse
  parser = argparse.ArgumentParser(description='Author: J. Olsson')
  parser.add_argument('--input', dest='input_file', type=str, required=True, help='Input JSON file')
  parser.add_argument('--out-directory', type=str, required=False, help='output directory', default='plots')
  parser.add_argument('-o', '--output', type=str, required=False, help='Name to put in output filenames', default='output')
  parser.add_argument('-b', '--batch', dest='batch_mode', action='store_true', help='Enable batch mode for ROOT.')
  parser.add_argument('--min-frac', dest='min_frac', type=float, required=False, default = '0.01', help='Minimum fraction for background to be included.')

  # parse the arguments, throw errors if missing any
  args = parser.parse_args()

  import json
  json_input = json.load(file(args.input_file))
  bkgd = json_input.get('bkgd')
  n_tot_bkgd = json_input.get('tot_bkgd').get('nevents')

  labels = []
  yields = []
  # explode = []
  for i in xrange(len(bkgd)):
    if float(bkgd[i].get('nevents'))/float(n_tot_bkgd) < args.min_frac: continue
    labels.append(bkgd[i].get('label'))
    yields.append(bkgd[i].get('nevents'))
    # explode.append(0.03)

  import matplotlib
  matplotlib.use('TkAgg')
  import matplotlib.pyplot as plt

  import seaborn as sns
  colors = sns.color_palette()
  import matplotlib.pylab as pylab
  params = {'legend.fontsize': 'xx-large',
            'figure.figsize': (6, 4),
           'axes.labelsize': 'x-large',
           'axes.titlesize':'x-large',
           'xtick.labelsize':'x-large',
           'ytick.labelsize':'x-large'}
  pylab.rcParams.update(params)

  fig1, ax1 = plt.subplots()
  ax1.pie(yields, labels=labels, labeldistance=1.15, shadow=False, autopct='%1.1f%%', colors=colors)
  ax1.axis('equal')
  fig1.savefig(re.sub('\.json', '.pdf', args.input_file), format='pdf')
