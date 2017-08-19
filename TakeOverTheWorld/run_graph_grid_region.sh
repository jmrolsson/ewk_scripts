#!/bin/bash

tag=Wh_SR_CR_VR_August15
sample=_HT_incl_filter

SR1=optimization_Wh_SR1_leptonveto_nJetsEq4_nBJetsEq2_dphiMinG0p4_dphiSum4jetG2p6_mbbG105L135_mNonbbG75L90_metG200_meffG900_mTbMinG100_mctbbG140
SR2=optimization_Wh_SR2_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_dphiSum4jetG2p6_mbbG105L135_mNonbbG75L90_metG250_meffG900_mTbMinG160_mctbbG140
SR3=optimization_Wh_SR3_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_dphiSum4jetG2p6_mbbG105L135_mNonbbG75L90_metG200_meffG700_mTbMinG180_mctbbG190

python graph_grid_region.py --summary cutflow_resolved/cutflow_Wh_SR_CR_VR_August15_HT_incl_filter/${SR1}.json --lumi 36 -o sensitivities_${SR1} -b --g-min 250 --g-max 750 --l-min 0 --l-max 250 --x-bin-size 50 --y-bin-size 50 --region SR1

python graph_grid_region.py --summary cutflow_resolved/cutflow_Wh_SR_CR_VR_August15_HT_incl_filter/${SR2}.json --lumi 36 -o sensitivities_${SR2} -b --g-min 250 --g-max 750 --l-min 0 --l-max 250 --x-bin-size 50 --y-bin-size 50 --region SR2

python graph_grid_region.py --summary cutflow_resolved/cutflow_Wh_SR_CR_VR_August15_HT_incl_filter/${SR3}.json --lumi 36 -o sensitivities_${SR3} -b --g-min 250 --g-max 750 --l-min 0 --l-max 250 --x-bin-size 50 --y-bin-size 50 --region SR3