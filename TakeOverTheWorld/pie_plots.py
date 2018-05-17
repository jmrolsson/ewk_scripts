import os
import re
import numpy as np

import matplotlib
matplotlib.use('TkAgg')
matplotlib.rcParams['font.size'] = 12.0
import matplotlib.pyplot as plt
from palettable import colorbrewer, tableau

if __name__ == '__main__':

  import argparse
  parser = argparse.ArgumentParser(description='Author: J. Olsson')
  parser.add_argument('--input', dest='input_file', type=str, required=True, help='Input JSON file')
  parser.add_argument('--out-directory', type=str, required=False, help='output directory', default='plots')
  parser.add_argument('-o', '--output', type=str, required=False, help='Name to put in output filenames', default='output')
  parser.add_argument('-b', '--batch', dest='batch_mode', action='store_true', help='Enable batch mode for ROOT.')
  parser.add_argument('--min-frac', type=float, required=False, default = '0.015', help='Minimum fraction for background to be included.')
  parser.add_argument('--max-ignore', type=float, required=False, default = '0.003', help='If more than this fraction is excluded in the end, plot slice with fraction of \'other\' backgrounds.')

  # parse the arguments, throw errors if missing any
  args = parser.parse_args()

  # load JSON
  import json
  json_input = json.load(file(args.input_file))
  bkgd = json_input.get('bkgd')
  ntotbkgd = json_input.get('tot_bkgd').get('nevents')

  labels = []
  yields = []

  # setup nice colors
  colors = tableau.Tableau_20.colors
  # Rescale to values between 0 and 1
  for i in range(len(colors)):
      r, g, b = colors[i]
      colors[i] = (r / 255., g / 255., b / 255.)

  colors_new = []
  for i in xrange(len(bkgd)):
    # print 'i {}, label {}, ratio {}, nevents {}, total {}'.format(i, bkgd[i].get('label'), float(bkgd[i].get('nevents'))/float(ntotbkgd), bkgd[i].get('nevents'), ntotbkgd)
    if float(bkgd[i].get('nevents'))/float(ntotbkgd) < args.min_frac: continue
    # print 'pass: {}'.format(bkgd[i].get('label'))
    labels.append(bkgd[i].get('label'))
    yields.append(bkgd[i].get('nevents'))
    # if (i < 2):
    #   colors_new.append(colors[len(bkgd)-i-1])
    # else:
    #   colors_new.append(colors[i-2])
    colors_new.append(colors[i])

  # foo = zip(yields, labels, colors_new)
  # foo.sort(reverse=True)
  # print zip(*foo)
  # yields, labels, colors_new = zip(*foo)
  ind = range(len(yields))
  ind.sort(key=lambda i:yields[i], reverse=True)
  yields = [yields[i] for i in ind]
  labels = [labels[i] for i in ind]
  colors_new = [colors_new[i] for i in ind]

  # add 'other' slice (if any)
  n_other = abs(sum(yields) - ntotbkgd)
  frac_other = abs(sum(yields)/ntotbkgd - 1.0)
  if frac_other > args.max_ignore:
      labels.append('other')
      yields.append(n_other)
      colors_new.append((211./255.,211./255.,211./255.)) # lightgray

  # normalize
  yields = np.array(yields)/sum(yields)

  # draw pie chart
  fig1, ax1 = plt.subplots()
  wedges = ax1.pie(yields, labels=labels, autopct='%1.1f%%', pctdistance=0.8, labeldistance=1.05, shadow=False, colors=colors_new)
  # for wedge in wedges[0]:
  #   wedge.set_edgecolor('white')
  ax1.axis('equal')
  fig1.savefig(re.sub('\.json', '_pie.pdf', args.input_file), format='pdf', bbox_inches='tight')
