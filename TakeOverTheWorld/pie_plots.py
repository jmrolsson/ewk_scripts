import os
import re
import json
import numpy as np

import matplotlib
matplotlib.use('TkAgg')
matplotlib.rcParams['font.size'] = 12.0
import matplotlib.pyplot as plt
from palettable import colorbrewer, tableau

def getColor(tag):

  colors = {'ttbar': (31, 119, 180),
            'singletop': (174, 199, 232),
            'Wjet': (44, 160, 44),
            'Zjet': (152, 223, 138),
            'ttV': (237, 201, 73),
            'diboson': (214, 39, 40)}

  c = colors.get(tag, None)
  if c:
    r, g, b = c
    return (r / 255., g / 255., b / 255.)
  return c

def byteify(input):
  if isinstance(input, dict):
    return {byteify(key): byteify(value)
      for key, value in input.iteritems()}
  elif isinstance(input, list):
    return [byteify(element) for element in input]
  elif isinstance(input, unicode):
    return input.encode('utf-8')
  else:
    return input

if __name__ == '__main__':

  import argparse

  config_parser = argparse.ArgumentParser(description="Configuration File", add_help=False)
  config_parser.add_argument('--config', type=str, nargs='+', required=True, help="The config JSON to load in")
  config_args, _ = config_parser.parse_known_args()
  configs = {}
  for config in config_args.config:
    configs.update(byteify(json.load(file(config))))

  parser = argparse.ArgumentParser(description='Author: J. Olsson')
  parser.add_argument('--input', dest='input_file', type=str, required=True, help='Input JSON file')
  parser.add_argument('--out-directory', type=str, required=False, help='output directory', default='plots')
  parser.add_argument('-o', '--output', type=str, required=False, help='Name to put in output filenames', default='output')
  parser.add_argument('-b', '--batch', dest='batch_mode', action='store_true', help='Enable batch mode for ROOT.')
  parser.add_argument('--min-frac', type=float, required=False, default = '0.00015', help='Minimum fraction for background to be included.')
  parser.add_argument('--max-ignore', type=float, required=False, default = '0.003', help='If more than this fraction is excluded in the end, plot slice with fraction of \'other\' backgrounds.')

  # parse the arguments, throw errors if missing any
  args, _ = parser.parse_known_args()

  # load JSON
  import json
  json_input = json.load(file(args.input_file))
  bkgd = json_input.get('bkgd')
  ntotbkgd = json_input.get('tot_bkgd').get('nevents')

  labels = []
  yields = []

  colors = []
  #for i in xrange(len(bkgd)):
  for i in [0, 1, 3, 4, 2, 5]:
    print 'i {}, label {}, ratio {}, nevents {}, total {}'.format(i, bkgd[i].get('label'), float(bkgd[i].get('nevents'))/float(ntotbkgd), bkgd[i].get('nevents'), ntotbkgd)
    if float(bkgd[i].get('nevents'))/float(ntotbkgd) < args.min_frac: continue
    print 'pass: {}'.format(bkgd[i].get('label'))
    yields.append(bkgd[i].get('nevents'))

    if '$t\\bar{t}$' in bkgd[i].get('label'):
      labels.append('$t\\bar{t}$')
      colors.append(getColor('ttbar'))
    elif 'single-top' in bkgd[i].get('label'):
      labels.append('Single-top')
      colors.append(getColor('singletop'))
    elif '$W$+jets 2.2.0' in bkgd[i].get('label'):
      labels.append('$W$+jets')
      colors.append(getColor('Wjet'))
    elif '$Z$+jets 2.2.0' in bkgd[i].get('label'):
      labels.append('$Z$+jets')
      colors.append(getColor('Zjet'))
    elif '$t\\bar{t}+X$' in bkgd[i].get('label'):
      labels.append('$t\\bar{t}V$')
      colors.append(getColor('ttV'))
    elif 'diboson' in bkgd[i].get('label'):
      labels.append('Diboson')
      colors.append(getColor('diboson'))
    else:
      continue

  # # add 'other' slice (if any)
  # n_other = abs(sum(yields) - ntotbkgd)
  # frac_other = abs(sum(yields)/ntotbkgd - 1.0)
  # if frac_other > args.max_ignore:
  #     labels.append('other')
  #     yields.append(n_other)
  #     colors.append((211./255.,211./255.,211./255.)) # lightgray

  # normalize
  yields = np.array(yields)/sum(yields)

  # draw pie chart
  fig1, ax1 = plt.subplots()
  wedges = ax1.pie(yields, labels=labels, autopct='%1.1f%%', pctdistance=0.8, labeldistance=1.05, shadow=False, colors=colors)
  # for wedge in wedges[0]:
  #   wedge.set_edgecolor('white')
  ax1.axis('equal')
  fig1.savefig(re.sub('\.json', '_pie.pdf', args.input_file), format='pdf', bbox_inches='tight')
