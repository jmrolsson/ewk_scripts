#!/bin/bash

#tag=Wh_SR_CR_VR_September30_HT_incl_filter
tag=Wh_SR_CR_VR_October18_HT_incl_filter_official_signal

SR1=optimization_Wh_SR1_leptonveto_nJetsEq4_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG900_mTbMinG140_mCTbbG140
SR2=optimization_Wh_SR2_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG250_meffG900_mTbMinG160_mCTbbG140
SR3=optimization_Wh_SR3_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG700_mTbMinG180_mCTbbG190

python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR1}.json --lumi 36 -o sensitivities_${SR1} -b --g-min 250 --g-max 750 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR1

python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR2}.json --lumi 36 -o sensitivities_${SR2} -b --g-min 250 --g-max 750 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR2

python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR3}.json --lumi 36 -o sensitivities_${SR3} -b --g-min 250 --g-max 750 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR3
