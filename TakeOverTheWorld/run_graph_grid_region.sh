#!/bin/bash

#tag=Wh_SR_CR_VR_November16_HT_incl_filter
#tag=Wh_SR_CR_VR_November16_MET_incl_filter
#tag=Wh_SR_CR_VR_January16_MET_incl_filter
tag=Wh_SR_CR_VR_January18_MET_incl_filter

# SR1=optimization_Wh_SR1_leptonveto_nJetsEq4_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG900_mTbMinG140_mCTbbG140
# SR2=optimization_Wh_SR2_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG250_meffG900_mTbMinG160_mCTbbG140
# SR2p=optimization_Wh_SR2prime_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG1000_mTbMinG160_mCTbbG140
# SR2pp=optimization_Wh_SR2prime_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG1000_mTbMinG140_mCTbbG140
# SR3=optimization_Wh_SR3_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG700_mTbMinG180_mCTbbG190
# SR3p=optimization_Wh_SR3prime_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG700L1000_mTbminG180_mCTbbG190
# SR3pp=optimization_Wh_SR3prime_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L90_metG200_meffG700L1000_mTbminG160_mCTbbG160

# SRlow=optimization_Wh_SRlow_leptonveto_nJetsEq4_nBJetsEq2_dphiMinG0p4_mbbG110L135_mNonbbG70L95_metG200_meffG700L1000_mTbminG100_mCTbbG140
# SRhigh=optimization_Wh_SRhigh_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG65L95_metG200_meffG1000_mTbminG140_mCTbbG140

SRlow=optimization_Wh_SRlow_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG75L85_metG200_meffG700_mTbminG140_mCTbbG200
SRmedium=optimization_Wh_SRmedium_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG70L90_metG200_meffG900_mTbminG140_mCTbbG140
SRhigh=optimization_Wh_SRhigh_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG105L135_mNonbbG65L95_metG200_meffG1000_mTbminG140_mCTbbG140

# SRlowp=optimization_Wh_SRlowprime_leptonveto_nJetsEq4_nBJetsEq2_dphiMinG0p4_mbbG110L135_mNonbbG70L95_metG200_meffG700_mTbminG100_mCTbbG140
# SRlowpp=optimization_Wh_SRlowprime_leptonveto_nJetsGeq4Leq5_nBJetsEq2_dphiMinG0p4_mbbG110L135_mNonbbG70L95_metG200_meffG700_mTbminG100_mCTbbG140

# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR1}.json --lumi 36.1 -o sensitivities_${SR1} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR1 --out-directory plots/sensitivity_${tag}
#
# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR2}.json --lumi 36.1 -o sensitivities_${SR2} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR2 --out-directory plots/sensitivity_${tag}
#
# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR2p}.json --lumi 36.1 -o sensitivities_${SR2p} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR2\' --out-directory plots/sensitivity_${tag}
#
# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR2pp}.json --lumi 36.1 -o sensitivities_${SR2pp} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR2\" --out-directory plots/sensitivity_${tag}
#
# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR3}.json --lumi 36.1 -o sensitivities_${SR3} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR3 --out-directory plots/sensitivity_${tag}
#
# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR3p}.json --lumi 36.1 -o sensitivities_${SR3p} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR3\' --out-directory plots/sensitivity_${tag}
#
# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SR3pp}.json --lumi 36.1 -o sensitivities_${SR3pp} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR3\" --out-directory plots/sensitivity_${tag}

python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SRlow}.json --lumi 36.1 -o sensitivities_${SRlow} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR1\' --out-directory plots/sensitivity_${tag}

# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SRlowp}.json --lumi 36.1 -o sensitivities_${SRlowp} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SRlow\' --out-directory plots/sensitivity_${tag}
#
# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SRlowpp}.json --lumi 36.1 -o sensitivities_${SRlowpp} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SRlow\" --out-directory plots/sensitivity_${tag}

python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SRmedium}.json --lumi 36.1 -o sensitivities_${SRmedium} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR2\' --out-directory plots/sensitivity_${tag}

python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SRhigh}.json --lumi 36.1 -o sensitivities_${SRhigh} -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region SR3\' --out-directory plots/sensitivity_${tag}

# python graph_grid_region.py --summary cutflow_resolved/cutflow_${tag}/${SRlow}.json cutflow_resolved/cutflow_${tag}/${SRhigh}.json --lumi 36.1 -o sensitivities_SRlow_SRhigh_combined -b --g-min 250 --g-max 900 --l-min 0 --l-max 250 --x-bin-size 25 --y-bin-size 25 --region "SR combination" --out-directory plots/sensitivity_${tag}
