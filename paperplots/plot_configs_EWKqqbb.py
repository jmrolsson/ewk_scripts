'''
Plotting config for the EWKqqbb HistFitter outputs
'''

import os
import re
import glob
import ROOT

luminosity = 36.1
lumiLabel = '#sqrt{{s}} = 13 TeV, {0:.1f} fb^{{-1}}'.format(luminosity)
atlasLabel = 'Internal'

weightsFile = 'weights_EWKqqbb.json'
cutsFile = 'cuts_EWKqqbb.json'

ratiomin = 0.01
ratiomax = 1.99

colors = {
  'ttbar': ROOT.TColor.GetColor('#1f77b4'),
  'singletop': ROOT.TColor.GetColor('#aec7e8'),
  'topEW': ROOT.TColor.GetColor('#ff7f0e'),
  'W_sherpa_220': ROOT.TColor.GetColor('#ffbb78'),
  'Z_sherpa_220': ROOT.TColor.GetColor('#2ca02c'),
  'diboson': ROOT.TColor.GetColor('#98df8a'),
  # 'dijet': ROOT.TColor.GetColor('#d62728'),
  'Wh_400p0_0p0': ROOT.TColor.GetColor('#d62728'),
  'Wh_500p0_0p0': ROOT.TColor.GetColor('#ff9896'),
  'Wh_550p0_0p0': ROOT.TColor.GetColor('#17becf'),
  'Wh_550p0_200p0': ROOT.TColor.GetColor('#9edae5'),
  'Wh_700p0_0p0': ROOT.TColor.GetColor('#e377c2'),
  'Data': ROOT.kBlack,
  'default': ROOT.kRed

  # tableau20 = [(31, 119, 180), (174, 199, 232), (255, 127, 14), (255, 187, 120),
  #            (44, 160, 44), (152, 223, 138), (214, 39, 40), (255, 152, 150),
  #            (148, 103, 189), (197, 176, 213), (140, 86, 75), (196, 156, 148),
  #            (227, 119, 194), (247, 182, 210), (127, 127, 127), (199, 199, 199),
  #            (188, 189, 34), (219, 219, 141), (23, 190, 207), (158, 218, 229)]

}

labels = {
  'ttbar': 't#bar{t}',
  'singletop': 'single top',
  'topEW': 't#bar{t}+X',
  'W_sherpa_220': 'W+jets',
  'Z_sherpa_220': 'Z+jets',
  'diboson': 'diboson',
  'Wh_400p0_0p0': '(400, 0)',
  'Wh_500p0_0p0': '(500, 0)',
  'Wh_550p0_0p0': '(550, 0)',
  'Wh_550p0_200p0': '(550, 200)',
  'Wh_700p0_0p0': '(700, 0)',
  'SR_LM': 'SRLM',
  'CRtt_LM': 'CRttLM',
  'CRst_LM': 'CRstLM',
  'CRZ_LM': 'CRZLM',
  'VRtt_LM': 'VRttLM',
  'VRSB_LM': 'VRSBLM',
  'VRbbhigh_LM': 'VRbbhighLM',
  'SR_HM': 'SRHM',
  'CRtt_HM': 'CRttHM',
  'CRst_HM': 'CRstHM',
  'CRZ_HM': 'CRZHM',
  'VRtt_HM': 'VRttHM',
  'VRSB_HM': 'VRSBHM',
  'VRbbhigh_HM': 'VRbbhighHM'
}

plotOptions = {
  'jets_n': {'xmin': 3.5, 'xmax': 8.5, 'ymin': 0.001, 'ymax': 500, 'titleX': 'N_{jet}', 'ticksX': 5},
  'bjets_n': {'xmin': 1.5, 'xmax': 4.5, 'ymin': 0.001, 'ymax': 500, 'titleX': 'N_{b-jet}', 'ticksX': 3},
  'dphi_min': {'xmin': 0, 'xmax': 3.20, 'ymin': 0.001, 'ymax': 300, 'titleX': '#Delta#phi^{4j}_{min}', 'ticksX': 208, 'ticksOpt': False},
  'met': {'xmin': 200, 'xmax': 600, 'ymin': 0.001, 'ymax': 300, 'titleX': 'E_{T}^{miss} [GeV]', 'ticksX': 410},
  'meff_4j': {'xmin': 700, 'xmax': 1500, 'ymin': 0.001, 'ymax': 300, 'titleX': 'm_{eff}^{4j} [GeV]', 'ticksX': 410},
  'ZCR_met': {'xmin': 200, 'xmax': 600, 'ymin': 0.001, 'ymax': 300, 'titleX': 'E_{T}^{miss} [GeV]', 'ticksX': 410},
  'ZCR_meff_4j': {'xmin': 700, 'xmax': 1500, 'ymin': 0.001, 'ymax': 300, 'titleX': 'm_{eff}^{4j} [GeV]', 'ticksX': 410},
  'mCT_bb': {'xmin': 0, 'xmax': 600, 'ymin': 0.001, 'ymax': 300, 'titleX': 'm_{CT}^{bb} [GeV]'},
  'mTb_min': {'xmin': 0, 'xmax': 600, 'ymin': 0.001, 'ymax': 300, 'titleX': 'm_{T}^{b,min} [GeV]'},
  'm_bb': {'xmin': 0, 'xmax': 600, 'ymin': 0.001, 'ymax': 300, 'titleX': 'm_{bb} [GeV]'},
  'm_non_bb': {'xmin': 0, 'xmax': 600, 'ymin': 0.001, 'ymax': 300, 'titleX': 'm_{qq} [GeV]'}
}

# samples to use
samples = ['ttbar', 'singletop', 'topEW', 'W_sherpa_220', 'Z_sherpa_220', 'diboson']
signalSamples = ['Wh_400p0_0p0', 'Wh_500p0_0p0', 'Wh_550p0_0p0', 'Wh_550p0_200p0', 'Wh_700p0_0p0']

# region to include
regions = ['LM', 'HM']
regionTypes = ['SR', 'CRtt', 'CRst', 'CRZ', 'VRtt', 'VRSB', 'VRbbhigh']

# plots to make
plotNames = plotOptions.keys()

fitTypes = ['beforeFit', 'afterFit']

inputDir = 'inputs/'
outDir = 'plots/'

allfiles = glob.glob(os.path.join(inputDir, '*.root*'))
allfiles.extend(glob.glob(os.path.join(inputDir, '*.merged*')))

def getChannels():
  channels = dict()
  for f in allfiles:
    if re.search('Wh_\d+p\d+_\d+p\d+', f): continue
    try:
      channel = os.path.basename(f)
      channel = channel[:channel.rindex('.')]
      tags = channel.split('_')
      if len(tags) > 1:
        regionType = tags[0]
        region = tags[1]
      plotName = [k for k in plotNames if '_{:s}_'.format(k) in channel][0]
      fitType = [k for k in fitTypes if k in channel][0]
      channels[channel] = {'regionType': regionType,
                           'region': region,
                           'plotName': plotName,
                           'fitType': fitType,
                           'filePath': f}
    except:
      continue

  return channels

def getSignalFiles():
  signalFiles = []
  for sample in signalSamples:
    signalFiles.extend( filter(lambda f: sample in f, allfiles) )
  return signalFiles
