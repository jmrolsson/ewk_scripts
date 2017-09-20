import os
import re
import numpy as np

import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

import seaborn as sns
import matplotlib.pylab as pylab
params = {'legend.fontsize': 'xx-large',
          'figure.figsize': (6, 4),
         'axes.labelsize': 'x-large',
         'axes.titlesize':'x-large',
         'xtick.labelsize':'x-large',
         'ytick.labelsize':'x-large'}
pylab.rcParams.update(params)

from palettable import colorbrewer, tableau

if __name__ == '__main__':

  import argparse
  parser = argparse.ArgumentParser(description='Author: J. Olsson')
  parser.add_argument('--input', dest='input_file', type=str, required=True, help='Input JSON file')
  parser.add_argument('--out-directory', type=str, required=False, help='output directory', default='plots')
  parser.add_argument('-o', '--output', type=str, required=False, help='Name to put in output filenames', default='output')
  parser.add_argument('-b', '--batch', dest='batch_mode', action='store_true', help='Enable batch mode for ROOT.')
  parser.add_argument('--min-frac', type=float, required=False, default = '0.01', help='Minimum fraction for background to be included.')
  parser.add_argument('--max-ignore', type=float, required=False, default = '0.03', help='If more than this fraction is excluded in the end, plot slice with fraction of \'other\' backgrounds.')

  # parse the arguments, throw errors if missing any
  args = parser.parse_args()

  import json
  json_input = json.load(file(args.input_file))
  bkgd = json_input.get('bkgd')
  ntotbkgd = json_input.get('tot_bkgd').get('nevents')

  labels = []
  yields = []

  colors_new = []
  colors = tableau.Tableau_20.colors
  # Rescale to values between 0 and 1
  for i in range(len(colors)):
      r, g, b = colors[i]
      colors[i] = (r / 255., g / 255., b / 255.)

  new_colors = []
  for i in xrange(len(bkgd)):
    if float(bkgd[i].get('nevents'))/float(ntotbkgd) < args.min_frac: continue
    labels.append(bkgd[i].get('label'))
    yields.append(bkgd[i].get('nevents'))
    if (i < 2):
      new_colors.append(colors[len(bkgd)-2])
    else:
      new_colors.append(colors[i-2])

  nother = abs(sum(yields)/ntotbkgd - 1)
  if nother > args.max_ignore:
      labels.append('Other')
      yields.append(nother)
      new_colors.append((211,211,211)) # lightgray

  fig1, ax1 = plt.subplots()
  ax1.pie(yields, labels=labels, labeldistance=1.15, shadow=False, autopct='%1.1f%%', colors=new_colors)
  ax1.axis('equal')
  fig1.savefig(re.sub('\.json', '.pdf', args.input_file), format='pdf')
