#!/usr/bin/env python

from __future__ import print_function
from ROOT import TFile, TH2D, TCanvas, gStyle, gROOT, gPad, kGray, kWhite, kBlack, TLatex
import sys
import os
import glob
import numpy as np


def main(argv):

    tag_data = 'overlay_diagnostic_data'
    tag_mc = 'overlay_diagnostic_mc'

    text_data = '#sqrt{s}=13 TeV, 36.1 fb^{-1}'

    text_selection = '#geq1L, #geq4j, #geq2b, E_{T}^{miss}>200 GeV, #Delta#phi^{4j}_{min}>0.4'

    filepatterns_data = ['*period*']

    groups_mc = ['ttbar', 'singletop', 'topEW', 'W_sherpa_220', 'Z_sherpa_220', 'dijet', 'diboson']
    texts_mc = ['t#bar{t}', 'single top', 't#bar{t}+X', 'W+jets (Sherpa 2.2.0)', 'Z+jets (Sherpa 2.2.0)', 'dijet', 'diboson']

    xtitle_lep = 'Leading lepton #phi'
    ytitle_lep = 'Leading lepton #eta'

    xtitle_jet = 'Leading jet #phi'
    ytitle_jet = 'Leading jet #eta'


    plot_hists(filepatterns_data, tag_data, text_data, text_selection, xtitle_lep, ytitle_lep)

    for i, group in enumerate(groups_mc):
        tag = '{:s}_{:s}'.format(tag_mc, group)
        filepatterns = ['*{:s}*'.format(group)]
        text = 'MC: {:s}'.format(texts_mc[i])
        plot_hists(filepatterns, tag, text, text_selection, xtitle_lep, ytitle_lep)

def plot_hists(filepatterns, tag, text, text_selection, xtitle, ytitle):

    ewkdir='/Users/joakim/GoogleDrive/CERN/Projects/Analysis-RunII/EWK/'
    inputdir='ewk_mbj_ntuples/tagEWKqqbb.2.4.37-0-histograms-noloosefilter/hf_diagnostic_checks_January24_MET_incl_filter/'
    inputdir = os.path.join(ewkdir,inputdir)

    histpath = 'hists/nLepGeq1_nJetsGeq4_nBJetsGeq2_metG200_dphiMinG0p4/'
    histnames = ['eta_vs_phi_lep_1']
    outputdir = 'plots'

    output = os.path.join(outputdir, histpath)
    ensure_dir(output)

    xmin = -np.pi
    xmax = np.pi
    ymin = -np.pi
    ymax = np.pi

    # Open files
    inputfiles = []
    for pattern in filepatterns:
        pattern = os.path.join(inputdir,pattern)
        inputfiles.extend(glob.glob(pattern))

    print('Opening input files:', inputfiles)
    tfiles = []
    for f in inputfiles:
        tfiles.append(TFile.Open(f))

    # Get hists
    hists = dict()
    for hname in histnames:
        for tf in tfiles:
            h = tf.Get(os.path.join(histpath,hname))
            try:
                hists[hname].Add(h)
            except KeyError:
                hists[hname] = h

    # Draw hists
    c1 = setup_canvas()
    for i, hname in enumerate(hists):
        c1.Clear()

        h = hists[hname]
        h.GetXaxis().SetTitle(xtitle)
        h.GetYaxis().SetTitle(ytitle)
        h.GetXaxis().SetRangeUser(xmin, xmax)
        h.GetYaxis().SetRangeUser(ymin, ymax)
        h.SetMarkerSize(0.15)
        h.Rebin(2)
        h.Draw('COL')
        c1.SetLogz()

        draw_atlas_label(0.2, 0.89, "Internal")
        draw_latex(0.2, 0.83, text, 0.04)
        draw_latex(0.2, 0.77, text_selection, 0.04)

        c1.SaveAs(os.path.join(output, "{:s}_{:s}.pdf".format(tag, hname)))
        c1.SaveAs(os.path.join(output, "{:s}_{:s}.png".format(tag, hname)))

    # Close files
    for f in tfiles:
        f.Close()

def setup_canvas(name = 'c1', title = "c1" , gridx = 0, gridy = 0, logx = 0, logy = 0, logz = 0, widthx = 800, widthy = 600, left_margin = 0.15, right_margin = 0.10):
    """ Initialize a canvas with appropriate settings """

    gStyle.SetOptStat(0)
    gStyle.SetTextAlign(21)
    gStyle.SetGridColor(kGray+1)
    gStyle.SetGridStyle(7)
    gStyle.SetGridWidth(2)
    gStyle.SetHatchesLineWidth(1)
    gStyle.SetHatchesSpacing(0.7)

    # Set canvas size
    gStyle.SetCanvasDefW(widthx);
    gStyle.SetCanvasDefH(widthy);

    # Create a canvas if one does not already exist
    if ("TCanvas" not in str(gROOT.FindObject(name))):
        c1 = TCanvas(name, title)
    else:
        c1 = gROOT.FindObject(name)

    c1.Clear()
    c1.Range(-10, -10, 10, 10)
    c1.SetFillColor(kWhite)
    c1.SetBorderMode(0)
    c1.SetBorderSize(2)
    c1.SetGridx(gridx)
    c1.SetGridy(gridy)
    c1.SetLogx(logx)
    c1.SetLogy(logy)
    c1.SetLogz(logz)
    c1.SetTickx()
    c1.SetTicky()
    c1.SetLeftMargin(left_margin)
    c1.SetRightMargin(right_margin)
    c1.SetTopMargin(0.08)
    c1.SetBottomMargin(0.15)

    return c1

def draw_atlas_label(x, y, text, color = kBlack):
    l = TLatex()
    l.SetNDC()
    l.SetTextAlign(13)
    l.SetTextFont(72)
    l.SetTextColor(color)

    delx = 0.115*696*gPad.GetWh()/(472*gPad.GetWw())

    l.DrawLatex(x,y,"ATLAS")
    if text:
        p = TLatex()
        p.SetNDC()
        p.SetTextAlign(13)
        p.SetTextFont(42)
        p.SetTextColor(color)
        p.DrawLatex(x+delx,y,text)

def draw_latex(x, y, text, size, color = kBlack):
    l = TLatex()
    l.SetNDC()
    l.SetTextFont(42)
    l.SetTextAlign(13)
    l.SetTextSize(size)
    l.SetTextColor(color)
    l.DrawLatex(x,y,text)

def ensure_dir(f):
    d = os.path.dirname(f)
    if not os.path.exists(d):
        os.makedirs(d)

if __name__ == "__main__":
    main(sys.argv)
