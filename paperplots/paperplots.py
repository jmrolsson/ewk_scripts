#!/usr/bin/env python
from __future__ import print_function
import sys, os, re, inspect, json
import numpy as np

# use inspect because of execfile
filename = inspect.getframeinfo(inspect.currentframe()).filename
sys.path.insert(0, os.path.dirname(os.path.realpath(filename)))

# load the plotting config file
import plot_configs_EWKqqbb as configs

def ensure_dir(f):
  d = os.path.dirname(f)
  if not os.path.exists(d):
    os.makedirs(d)

def getSampleColor(sample):
  return configs.colors.get(sample, 'default')

def getLabel(key):
  try:
    label = configs.labels.get(key)
  except KeyError:
    label = key # if not found then use the key as label
  return label

def setupCanvas(name='canvas', title='canvas', width=700, height=600):
  # Create a canvas if one does not already exist
  if ('TCanvas' not in str(ROOT.gROOT.FindObject(name))):
    canvas = TCanvas(name, title, width, height)
  else:
    canvas = ROOT.gROOT.FindObject(name)
    canvas.Clear() # clear the recycled canvas
  return canvas

def setupLegend(nentries=1, ncol=1, x1=0.70, y1=0.45, x2=0.95, y2=0.86, alpha = False):
  # Initialize a legend with appropriate settings
  legend = TLegend(x1, y1, x2, y2)
  if (nentries > 2):
    legend.SetNColumns(ncol)
  legend.SetLineColor(ROOT.kWhite)
  legend.SetFillColor(ROOT.kWhite)
  legend.SetTextColor(1)
  legend.SetTextFont(42)
  legend.SetLineStyle(0)
  legend.SetLineWidth(0)
  legend.SetBorderSize(0)
  if alpha:
    legend.SetFillStyle(1001)
    legend.SetFillColorAlpha(kGray, 0.95)
  else:
    legend.SetFillStyle(0)
  return legend

def get_did(fileName):
  if re.search('\d{6,8}', fileName):
    return re.search('\d{6,8}', fileName).group()
  else:
    raise ValueError('No did was found for file {}'.format(fileName))

def getScaleFactor(did, weights, luminosity):
  weight = weights.get(did)
  if weight is None:
    raise KeyError('Could not find the weights for did=%s' % did)
  scaleFactor = 1.0
  if weight.get('num events') == 0:
    raise ValueError('did=%s has num events == 0' % did)
  scaleFactor /= weight.get('num events')
  scaleFactor *= weight.get('cross section')
  scaleFactor *= weight.get('filter efficiency')
  scaleFactor *= weight.get('k-factor')
  scaleFactor *= luminosity*1000
  # print('Scale factor for %s: %0.6f' % (did, scaleFactor))
  return scaleFactor

if __name__ == '__main__':

  import argparse
  parser = argparse.ArgumentParser(description='Specify options for pretty HistFitter plots')
  parser.add_argument('--regions',       type=str, nargs='+', default=configs.regions, help='List of regions to run over (E.g. LM, HM)')
  parser.add_argument('--regionTypes',   type=str, nargs='+', default=configs.regionTypes, help='List of region types (E.g. SR, CR, VR)')
  parser.add_argument('--atlasLabel',    type=str, default=configs.atlasLabel, help='ATLAS label (E.g. Internal/Preliminary)')
  parser.add_argument('--lumiLabel',     type=str, default=configs.lumiLabel, help='Luminosity label (E.g. #sqrt{s} = 13 TeV, 36.1 fb^{-1})')
  parser.add_argument('--luminosity',    type=float, default=configs.luminosity, help='Luminosity in invfb')
  parser.add_argument('--ratiomin',      type=float, default=configs.ratiomin, help='Minimum ratio range')
  parser.add_argument('--ratiomax',      type=float, default=configs.ratiomax, help='Maximumr ratio range')
  parser.add_argument('--weights',       type=str, dest='weightsFile', default=configs.weightsFile, metavar='<file.json>', help='json file specifying the weights by dataset id')
  parser.add_argument('--cuts',          type=str, dest='cutsFile', default=configs.cutsFile, metavar='<file.json>', help='json file specifying the region cuts')
  parser.add_argument('-i', '--input',   type=str, dest='inputDir', default=configs.inputDir, help='Top level directory containing plots')
  parser.add_argument('-o', '--output',  type=str, dest='outDir', default=configs.outDir, help='Output file path')
  parser.add_argument('--file-ext',      type=str, nargs='+', default=['pdf'], help='Output file extensions to make')
  parser.add_argument('--file-prefix',   type=str, default='dataMC', help='Output file extensions to make')
  parser.add_argument('--limits',        dest='draw_limits', action='store_true')
  parser.add_argument('-v','--verbose',  dest='verbose', action='count', default=0, help='Enable verbose output of various levels')

  args, _ = parser.parse_known_args()

  ensure_dir(args.outDir)

  # Setup root
  import ROOT
  from ROOT import TFile, THStack, TCanvas, TLegend, TPad, TH1F, TLine, TArrow
  ROOT.PyConfig.IgnoreCommandLineOptions = True
  ROOT.gROOT.SetBatch(True)
  ROOT.gStyle.SetOptStat(0)

  # Get list of channels
  channels = configs.getChannels()

  # Load json with weights file (for rescaling signal samples)
  weights = json.load(file(args.weightsFile))

  # Load file with region cuts
  cuts= json.load(file(args.cutsFile))

  # Load signal files
  signalFiles = configs.getSignalFiles()

  # Make one plot for each channel
  for channel, metadata in channels.iteritems():
    print('----> Processing channel: ', channel)

    region = metadata['region']
    regionType = metadata['regionType']
    plotName = metadata['plotName']
    filePath = metadata['filePath']

    if not os.path.exists(filePath):
      print('Warning: file \'{}\' does not exist'.format(filePath))
      continue
    f = TFile.Open(filePath)

    canvas = setupCanvas()

    pad1 = TPad('pad1', 'pad1', 0, 0.30, 1, 1)
    pad1.SetRightMargin(0.1)
    pad1.SetLeftMargin(0.15)
    pad1.SetBottomMargin(0.0)
    pad1.SetFillColor(ROOT.kWhite)
    pad1.SetTickx()
    pad1.SetTicky()

    pad2 = TPad('pad2', 'pad2', 0, 0, 1, 0.3)
    pad2.SetRightMargin(0.1)
    pad2.SetLeftMargin(0.15)
    pad2.SetBottomMargin(0.3)
    pad2.SetTopMargin(0.0);
    pad2.SetFillColor(ROOT.kWhite)
    pad2.SetTickx()
    pad2.SetTicky()

    pad1.Draw()
    pad2.Draw()

    pad1.cd()
    # pad1.SetLogy()

    xmin = configs.plotOptions[plotName]['xmin']
    xmax = configs.plotOptions[plotName]['xmax']

    ticksX = configs.plotOptions[plotName].get('ticksX', 510)
    ticksOpt = configs.plotOptions[plotName].get('ticksOpt', True)

    hBkgStack = THStack('bkg', '')
    for sample in configs.samples:
      h = f.Get(sample)
      if 'TH1' not in str(h): continue
      h.SetFillColor(getSampleColor(sample))
      h.SetLineColor(getSampleColor(sample))
      hBkgStack.Add(h)
    hBkgStack.Draw('hist')
    #hBkgStack.SetMaximum(configs.plotOptions[plotName]['ymax'])
    hBkgStack.SetMaximum(hBkgStack.GetMaximum()*2.2)
    hBkgStack.SetMinimum(0.001)
    hBkgStack.GetXaxis().SetRangeUser(xmin, xmax)
    hBkgStack.GetXaxis().SetTitle('')
    hBkgStack.GetYaxis().SetTitle('Events')
    hBkgStack.GetXaxis().SetTitleOffset(1.2)
    hBkgStack.GetYaxis().SetTitleOffset(1.4)
    hBkgStack.GetXaxis().SetTitleSize(0.00)
    hBkgStack.GetYaxis().SetTitleSize(0.05)
    hBkgStack.GetXaxis().SetLabelSize(0.00)
    hBkgStack.GetYaxis().SetLabelSize(0.05)
    hBkgStack.GetYaxis().SetNdivisions(510)
    hBkgStack.GetXaxis().SetNdivisions(ticksX, ticksOpt)

    hSM = f.Get('SM_total')
    hSM.SetLineColor(ROOT.kRed)
    hSM.SetLineWidth(2)
    hSM.Draw('hist same')

    hErr = f.Get('h_total_error_band')
    hErr.SetFillStyle(3004)
    hErr.SetLineStyle(ROOT.kDashed)
    hErr.SetLineColor(ROOT.kBlack)
    hErr.Draw('F')

    data = f.Get('h_obsData')
    data.Draw('P same')

    if 'SR' in channel:
      legend = setupLegend(y1=0.35)
    else:
      legend = setupLegend()
    legend.AddEntry(data, 'Data', 'p')
    entry = ROOT.TLegendEntry()
    entry.SetFillColor(ROOT.kBlack);
    entry.SetLineColor(ROOT.kRed);
    entry.SetMarkerColor(ROOT.kRed)
    entry.SetMarkerStyle(0)
    entry.SetMarkerSize(0)
    entry.SetFillStyle(3004);
    legend.AddEntry(entry, 'SM total', 'lf')

    # Add background samples to legend
    for sample in configs.samples:
      h = f.Get(sample)
      if 'TH1' not in str(h): continue
      h.SetFillColor(getSampleColor(sample))
      h.SetLineColor(getSampleColor(sample))
      legend.AddEntry(h, getLabel(sample), 'f')

  # for filePath in signalFiles:
  #   if not os.path.exists(filePath):
  #     print('Warning: signal file \'{}\' does not exist'.format(filePath))
  #     continue
  #   signals.append(TFile.Open(filePath))

    # Draw signals and add to legend
    minimum = hBkgStack.GetMinimum()
    maximum = hBkgStack.GetMaximum()

    if 'SR' in regionType:
      signals = [TFile.Open(s) for s in signalFiles if os.path.exists(s)]
      for signal, signalFile, signalSample in zip(signals, signalFiles, configs.signalSamples):
        h = signal.Get('hists/{0:s}_{1:s}_Nm1_{2:s}/{2:s}'.format(regionType, region, plotName))
        if 'TH1' not in str(h): continue
        h.SetFillColor(getSampleColor(signalSample))
        h.SetLineColor(getSampleColor(signalSample))
        h.SetLineWidth(2)
        h.SetLineStyle(2)
        h.SetFillStyle(0)
        h.Scale(getScaleFactor(get_did(signalFile), weights, args.luminosity))
        h.DrawCopy('hist same')
        legend.AddEntry(h, getLabel(signalSample), 'l')
        if h.GetMaximum()>maximum:
          maximum = h.GetMaximum()

    hBkgStack.SetMaximum(maximum*2.2)
    canvas.Update()

    legend.Draw()

    pad2.cd()

    hist1 = TH1F('h1', 'h1', 100, xmin, xmax)
    hist1.SetTitle('')
    hist1.GetYaxis().SetRangeUser(args.ratiomin, args.ratiomax)
    hist1.GetXaxis().SetRangeUser(xmin, xmax)
    hist1.GetXaxis().SetTitle(configs.plotOptions[plotName]['titleX'])
    hist1.GetYaxis().SetTitle('Data/SM')
    hist1.GetXaxis().SetTitleOffset(1.0)
    hist1.GetYaxis().SetTitleOffset(0.6)
    hist1.GetYaxis().SetNdivisions(404)
    hist1.GetXaxis().SetNdivisions(ticksX, ticksOpt)
    hist1.GetXaxis().SetTitleSize(0.12)
    hist1.GetYaxis().SetTitleSize(0.12)
    hist1.GetXaxis().SetLabelSize(0.12)
    hist1.GetYaxis().SetLabelSize(0.12)
    hist1.GetXaxis().SetTickSize(0.07)
    hist1.Draw()

    line1 = TLine(xmin, 1, xmax, 1)
    line1.SetLineStyle(2)
    line1.Draw()

    line2 = TLine(xmin, 1.5, xmax, 1.5)
    line2.SetLineStyle(3)
    line2.Draw()

    line3 = TLine(xmin, 0.5, xmax, 0.5)
    line3.SetLineStyle(3)
    line3.Draw()

    dataRatio = f.Get('h_ratio')
    dataRatio.Draw('same P')

    oflowval = ROOT.TLatex()
    oflowval.SetTextFont(62)
    oflowval.SetTextSize(0.05)
    oflowval.SetTextColor(ROOT.kBlack)
    ratiox = np.array(dataRatio.GetX())
    ratioy = np.array(dataRatio.GetY())
    oflowarrs = []
    for (x,y) in zip(ratiox, ratioy):
      if y>args.ratiomax and x>xmin and x<xmax:
        if abs(x-xmax)/xmax < 0.1:
          oflowval.DrawLatex(x-xmax*0.025, args.ratiomax*0.85, '{0:.1f}'.format(y))
        else:
          oflowval.DrawLatex(x+xmax*0.010, args.ratiomax*0.85, '{0:.1f}'.format(y))
        oflowarrs.append(TArrow(x, args.ratiomax*0.85, x, args.ratiomax*0.995))

    for arr in oflowarrs:
      arr.SetLineStyle(1)
      arr.SetLineWidth(1)
      arr.SetLineColor(ROOT.kBlack)
      arr.SetArrowSize(0.01)
      arr.Draw()

    # import pdb; pdb.set_trace()

    hErrRel = f.Get('h_rel_error_band')
    hErrRel.SetFillStyle(3004)
    hErrRel.SetLineStyle(ROOT.kDashed)
    hErrRel.SetLineColor(ROOT.kBlack)
    hErrRel.Draw('F')

    canvas.cd()

    latexObject = ROOT.TLatex()
    latexObject.SetTextSize(0.042)
    latexObject.SetTextFont(72)
    latexObject.DrawLatexNDC(0.20, 0.87, 'ATLAS')
    latexObject.SetTextFont(42)
    latexObject.DrawLatexNDC(0.32, 0.87, args.atlasLabel)
    latexObject.DrawLatexNDC(0.20, 0.82, args.lumiLabel)
    latexObject.SetTextFont(62)
    latexObject.SetTextSize(0.038)
    if 'Nm1' in channel:
      latexObject.DrawLatexNDC(0.20, 0.77, '{} (N-1 cuts)'.format(getLabel('{}_{}'.format(regionType, region))))
    else:
      latexObject.DrawLatexNDC(0.20, 0.77, getLabel('{}_{}'.format(regionType, region)))

    if args.draw_limits and 'Nm1' in channel:

      pad1.cd()

      try:

        ymaxScaleFac = 1.4

        cutKey = channel[:channel.rindex('Nm1')-1]
        plotCuts = [k.replace(' ', '') for k in cuts[cutKey].split('&&') if ' {0:s} '.format(plotName) in k]

        # hack for jets_n, bjets_n
        if any(k for k in plotCuts if re.search('^{}'.format('jets_n'), k)):
          plotCuts = ['jets_n<=5.5']
        if any(k for k in plotCuts if re.search('^{}'.format('bjets_n'), k)):
          # plotCuts = ['bjets_n>=1.5', 'bjets_n<=2.5']
          plotCuts = ['bjets_n<=2.5']

        if len(plotCuts) == 1:

          limit = float(re.findall('^\d+\.*\d*|\d+\.*\d*$', plotCuts[0])[0])

          if (abs((limit-xmax)/float(xmax)) > 0.90 or abs((limit-.0001-xmin)/float(.0001+xmin)) > 0.1):

            upperbound = False
            if '<' in plotCuts[0]:
              upperbound = True

            ll = TLine(limit, minimum, limit, maximum*ymaxScaleFac)
            ll.SetLineStyle(1)
            ll.SetLineWidth(2)
            ll.SetLineColor(ROOT.kGray+3)
            ll.Draw()

            arrlength = 0.2*abs((xmax-xmin))
            if upperbound:
              arr = TArrow(limit, maximum*ymaxScaleFac, limit-arrlength, maximum*ymaxScaleFac)
            else:
              arr = TArrow(limit, maximum*ymaxScaleFac, limit+arrlength, maximum*ymaxScaleFac)
            arr.SetLineStyle(1)
            arr.SetLineWidth(2)
            arr.SetLineColor(ROOT.kGray+3)
            arr.SetArrowSize(0.015)
            arr.Draw()

            symbol = re.findall('(?<={0:s})>|<|<=|>=(?=\d)'.format(plotName), plotCuts[0])[0]
            cuttext = '{0:s}{1:s}{2:2g}'.format(configs.plotOptions[plotName]['titleX'], symbol, limit)
            # hack for jets_n, bjets_n
            if any(k for k in plotCuts if re.search('^{}'.format('jets_n'), k)):
              cuttext = '4 #leq N_{jet} #leq 5'
            elif any(k for k in plotCuts if re.search('^{}'.format('bjets_n'), k)):
              cuttext = 'N_{b-jet} = 2'
            cuttext = cuttext.replace('[GeV]', '')
            cuttext = cuttext.replace(' ', '')
            latexObject.SetTextColor(ROOT.kGray+3)
            if upperbound:
              latexObject.DrawLatex(limit-0.8*arrlength, maximum*ymaxScaleFac*1.05, cuttext)
            else:
              latexObject.DrawLatex(limit+0.2*arrlength, maximum*ymaxScaleFac*1.05, cuttext)

        elif len(plotCuts) == 2:

          limits = [float(re.findall('^\d+\.*\d*|\d+\.*\d*$', l)[0]) for l in plotCuts]

          ll1 = TLine(limits[0], minimum, limits[0], maximum*ymaxScaleFac)
          ll1.SetLineStyle(1)
          ll1.SetLineWidth(2)
          ll1.SetLineColor(ROOT.kGray+3)
          ll1.Draw()
          ll2 = TLine(limits[1], minimum, limits[1], maximum*ymaxScaleFac)
          ll2.SetLineStyle(1)
          ll2.SetLineWidth(2)
          ll2.SetLineColor(ROOT.kGray+3)
          ll2.Draw()

          arrlength = 0.05*abs((xmax-xmin))
          arr1 = TArrow(limits[0]-arrlength, maximum*ymaxScaleFac*0.95, limits[0]-arrlength*0.10, maximum*ymaxScaleFac*0.95)
          arr1.SetLineStyle(1)
          arr1.SetLineWidth(2)
          arr1.SetLineColor(ROOT.kGray+3)
          arr1.SetArrowSize(0.015)
          arr1.Draw()
          arr2 = TArrow(limits[1]+arrlength, maximum*ymaxScaleFac*0.95, limits[1]+arrlength*0.10, maximum*ymaxScaleFac*0.95)
          arr2.SetLineStyle(1)
          arr2.SetLineWidth(2)
          arr2.SetLineColor(ROOT.kGray+3)
          arr2.SetArrowSize(0.015)
          arr2.Draw()

          cuttext = '{1:2g} #leq {0:s} #leq {2:2g}'.format(configs.plotOptions[plotName]['titleX'], limits[0], limits[1])
          cuttext = cuttext.replace('[GeV]', '')
          cuttext = cuttext.replace(' ', '')
          latexObject.SetTextColor(ROOT.kGray+3)
          latexObject.DrawLatex(limits[0]-arrlength, maximum*ymaxScaleFac*1.05, cuttext)

      except Exception as e:
        print(e)
        print('Warning: no region boundaries drawn for: {0:s}'.format(plotName))

    canvas.cd()
    canvas.Update()
    canvas.SaveAs(os.path.join(configs.outDir, 'dataMC_{}.pdf'.format(channel)))

    canvas.Clear()
    f.Close()

  print('All done')

