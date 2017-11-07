#! /usr/bin/env python
from __future__ import print_function
import ROOT
import glob
import os
import re

ibin = 1
file_path = "/Users/joakim/ewk/ewk_mbj_ntuples/histfitter/2.4.33-5-0-52-g169a7c2-histograms/hf_cutflow_Wh_SR_CR_VR_October18_HT_incl_filter/"

os.chdir(file_path)
# print(os.getcwd())
files = sorted(glob.glob('*.hists'.format(file_path)))
# print(files)
if files:
    for f in files:
        # print('\n----> File name: {}'.format(f))
        tf = ROOT.TFile.Open(f)
        h = tf.Get('hists/all/cutflow')
        nevents = h.GetBinContent(ibin)
        masspoint = re.search('\d+p\d+_\d+p\d+', f).group()
        did = int(re.search('394\d+', f).group())
        print('{} ({:d}): {:.2f}'.format(masspoint, did, nevents))



