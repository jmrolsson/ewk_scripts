#! /usr/bin/env python
import fnmatch
import subprocess
import os
import sys
import io
import re
import math

import numpy as np
import scipy as sp
import pylab as pl
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

from matplotlib.backends.backend_pdf import PdfPages
from scipy.interpolate import interp1d

import prettyplotlib as ppl
from prettyplotlib import brewer2mpl
#import seaborn as sns

from PlotFunctions import *
from ROOT import *

##
## Main script
##

algo_type = sys.argv[1]
btag = sys.argv[2]

# Global config
do_all = False
do_debug = False
do_norm = True
do_zoom = False
do_norm_noBtags = True
do_norm_2Btags = False

do_subjet = False

# Add ABCD lines to 2D plot
add_lines = False
line_x_pos = 0.1
line_y_pos = 0.3

# Plot draw options
draw_style = "box"
marker_type = "box2D"

# Re-binning
rebin = 5
if do_zoom:
    rebin = 5

# Global variables
atlas_label = "Internal"

file_tag = "run45"
folder_tag = "ABCD_vary_nBtags_equal_geq"

output_file_tag = file_tag+"_SR_optimization2"

if do_norm_noBtags:
    output_file_tag += "_normToIncl"
elif do_norm_2Btags:
    output_file_tag += "_normTo2Btags"
elif do_norm:
    output_file_tag += "_norm"

if do_subjet:
    output_file_tag += "_passSubjetRatioCut"

if do_zoom:
    output_file_tag += "_zoom"

if add_lines:
    output_file_tag += "_line"

# I/O
path = "/Users/joakim/cern/analysis/rpv_StopBS/"
input_dir  = path+"results/histogramFiles/NTUP_COMMON/"+file_tag+"_"+folder_tag+"/"
output_dir = path+"/results/plots_common/overlay_SR_optimization_new_Dec27/"

treename = "j145_a4_ht500"

trigger = "j145_a4_ht500"

if (algo_type == "AKT"):
    #jet_algo_list = ["AntiKt10LCTopoTrimmedPtFrac5SmallR30","RAKT10Sp_AntiKt4LCTopo","RAKT12Sp_AntiKt4LCTopo","RAKT15Sp_AntiKt4LCTopo","RAKT17Sp_AntiKt4LCTopo"]
    #jet_algo_list = ["RAKT10Sp_AntiKt4LCTopo","RAKT12Sp_AntiKt4LCTopo","RAKT15Sp_AntiKt4LCTopo","RAKT17Sp_AntiKt4LCTopo"]
    jet_algo_list = ["RAKT15Sp_AntiKt4LCTopo"]
elif (algo_type == "CA"):
    #jet_algo_list = ["CamKt12LCTopoSplitFilteredmassFraction67minSplitR0","RCA10Sp_AntiKt4LCTopo","RCA12Sp_AntiKt4LCTopo","RCA15Sp_AntiKt4LCTopo","RCA17Sp_AntiKt4LCTopo"]
    jet_algo_list = ["RCA10Sp_AntiKt4LCTopo","RCA12Sp_AntiKt4LCTopo","RCA15Sp_AntiKt4LCTopo","RCA17Sp_AntiKt4LCTopo"]
elif  (algo_type == "ALL"):
    jet_algo_list = ["RAKT10Sp_AntiKt4LCTopo","RAKT12Sp_AntiKt4LCTopo","RAKT15Sp_AntiKt4LCTopo","RAKT17Sp_AntiKt4LCTopo",
                     "RCA10Sp_AntiKt4LCTopo","RCA12Sp_AntiKt4LCTopo","RCA15Sp_AntiKt4LCTopo","RCA17Sp_AntiKt4LCTopo"]
else:
    print "ERROR: Input argument needs to be either 'AKT', 'CA' or 'ALL'"
    exit()

preselection = "NjetIncl_NFatJetMin2"

if btag == "noBtag":
    cut = "noBtags"
    leg_tag_list  = ["Preselection", "Inclusive b-tag region (#geq 0)"]
elif btag == "eventBtag":
    cut = "2Btags"
    leg_tag_list = ["Preselection", "#geq 2 b-tags/event"]
elif btag == "jetBtag":
    cut = "2Btags_2BtagsFatJet"
    leg_tag_list = ["Preselection", "#geq 2 b-tags/event", "#geq 2 b-tags in fat jets"]
else:
    print "ERROR: Incorrect run number"
    exit()

# Normalization
if (do_norm_noBtags):
    cut_ref = "noBtags"
elif (do_norm_2Btags):
    cut_ref = "2Btags"
else:
    cut_ref = cut

if do_subjet:
    cut += "_highSubjetRatio30"
    cut_ref += "_highSubjetRatio30"
    leg_tag_list.append("Subjet p_{T2}/p_{T1} > 0.3")

plot = "CMangle_vs_massAsym12"

if not os.path.isdir(output_dir):
    os.makedirs(output_dir)

# Clear output dir
#subprocess.Popen("rm -r "+output_dir+"*", shell=True, stdout=subprocess.PIPE)

# List of gluino masses
if do_all:
    stop_mass_list = [100, 125, 150, 175,
                      200, 225, 250, 275,
                      300, 325, 350, 375,
                      400, 425, 450, 475,
                      500, 525, 550]
else:
#    stop_mass_list = [100, 200, 300, 400, 500]
    stop_mass_list = [200]


bkgd_file = TFile(input_dir+file_tag+".herwigpp_JZXW.COMMON.root", "READ")

sig_file_list = []
for stopmass in stop_mass_list:
    file_path = input_dir+file_tag+".hpp_RPV_DirectStop_8TeV_T"+str(stopmass)+".COMMON.root"
    sig_file_list.append(file_path)

if (len(sig_file_list) == 0):
    print "ERROR: No input files"
    exit()

# Open all signal in ROOT
sig_files = [TFile(fname, "READ") for fname in sig_file_list]

# List for figuring out/store the legend labels
for i, jet_algo in enumerate(jet_algo_list):

    histo_path = treename+"/"+jet_algo+"_"+trigger+"_"+preselection+"_"+cut+"_"+plot
    histo_path_ref = treename+"/"+jet_algo+"_"+trigger+"_"+preselection+"_"+cut_ref+"_"+plot

    h_bkgd = bkgd_file.Get(histo_path)
    h_bkgd.Rebin2D(rebin, rebin)

    h_bkgd_ref = bkgd_file.Get(histo_path_ref)
    if (cut_ref != cut):
        h_bkgd_ref.Rebin2D(rebin, rebin)

    print "h_bkgd_ref.Integral()  " + str(h_bkgd_ref.Integral())
    print "h_bkgd.Integral()      " + str(h_bkgd.Integral())
    print "h_bkgd.GetBinContent(10,10) " + str(h_bkgd.GetBinContent(10,10))

    if do_norm:
        if (h_bkgd_ref.Integral() != 0):
            #norm = h_bkgd.Integral()/h_bkgd_ref.Integral()
            norm = 1./h_bkgd_ref.Integral()
            h_bkgd.Scale(norm)
            print "norm " + str(norm)

    print "---------------------"
    print "h_bkgd_ref.Integral()  " + str(h_bkgd_ref.Integral())
    print "h_bkgd.Integral()      " + str(h_bkgd.Integral())
    print "h_bkgd.GetBinContent(10,10) " + str(h_bkgd.GetBinContent(10,10))
    print "####################"

    algo_label = ""
    algo_tag = "missingAlgoTag"
    if ("CamKt12LCTopoSplitFilteredmassFraction67minSplitR0" in jet_algo):
        algo_label = "Std. C/A (R=1.2, Sp-Filt)"
        algo_tag = "CA12SpFl"

    elif ("AntiKt10LCTopoTrimmedPtFrac5SmallR30" in jet_algo):
        algo_label = "Std. anti-k_{t} (R=1.0, Trim)"
        algo_tag = "AKT10Trim"

    elif re.search("RCA\d+Sp_AntiKt4LCTopo", jet_algo):
        radius = re.search("(?<=RCA)\d+",jet_algo).group()
        algo_label = "Re-clust. C/A R = "+str(float(radius)/10) + " (splitting)"
        algo_tag = "RCA"+str(int(radius))+"Sp"

    elif re.search("RAKT\d+Sp_AntiKt4LCTopo", jet_algo):
        radius = re.search("(?<=AKT)\d+",jet_algo).group()
        algo_label = "Re-clust. anti-k_{t} R = "+str(float(radius)/10) + " (splitting)"
        algo_tag = "RAKT"+str(int(radius))+"Sp"

    for j, f in enumerate(sig_files):

        output_name = output_file_tag+"_T"+str(stop_mass_list[j])+"_"+plot+"_"+trigger+"_"+cut+"_"+algo_tag

        leg_entry_list = ["H++ (dijets)", "m_{#tilde{t}} = " + str(stop_mass_list[j]) + " [GeV]"]

        h_sig = f.Get(histo_path)
        h_sig.Rebin2D(rebin, rebin)

        h_sig_ref = f.Get(histo_path_ref)
        if (cut_ref != cut):
            h_sig_ref.Rebin2D(rebin, rebin)

        print "h_sig_ref.Integral()  " + str(h_sig_ref.Integral())
        print "h_sig.Integral()      " + str(h_sig.Integral())
        print "h_sig.GetBinContent(10,10) " + str(h_sig.GetBinContent(10,10))

        if do_norm:
            if (h_sig_ref.Integral() != 0):
                #norm = h_sig.Integral()/h_sig_ref.Integral()
                norm = 1./h_sig_ref.Integral()
                h_sig.Scale(norm)
                print "norm " + str(norm)

        print "---------------------"
        print "h_sig_ref.Integral()  " + str(h_sig_ref.Integral())
        print "h_sig.Integral()      " + str(h_sig.Integral())
        print "h_sig.GetBinContent(10,10) " + str(h_sig.GetBinContent(10,10))
        print "####################"

        # Set plot style attributes
        options = "sigBkgd_overlay_2D_box"
        if do_zoom:
            options += "zoom"
        if add_lines:
            options += "line"
        if do_subjet:
            options += "subjet"
        plot_attrib = setAttributes(plot, atlas_label, "", do_norm, options)

        # Overlay and save histograms to file
        overlay2DHistograms([h_bkgd, h_sig],
                            [algo_label]+leg_tag_list,
                            leg_entry_list,
                            output_dir,
                            output_name,
                            plot_attrib,
                            draw_style,
                            marker_type,
                            do_norm,
                            add_lines,
                            line_x_pos, line_y_pos)
