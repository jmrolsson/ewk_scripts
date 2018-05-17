#!/bin/bash

tag="tagEWKqqbb.2.4.37-0-2-gd931f07"
out_tag="tagEWKqqbb.2.4.37-0-2-gd931f07-histograms-noloosefilter"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples

#filter=_sherpa_220_only
#cuts_tag=hf_main_variables_systematics_February23
#cuts_tag=hf_Nm1_SR2_February23
#cuts_tag=hf_Nm1_SR3_February23

filter=_sherpa_221_only
#cuts_tag=hf_main_variables_systematics_February23
cuts_tag=hf_Nm1_SR2_February23

suffix=merged

event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2*weight_pu"
event_weight_syst="weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2*weight_pu"

dids_to_process=dids_to_process$filter.txt
while read did; do
  echo "Processing: ${did}"

  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_loose.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${out_tag}/${cuts_tag}${filter}_nominal/ ${ntuple_path}/${tag}/*${did}*.${suffix}* &

  #for syst_weight in "ckkw15_Weight" "ckkw30_Weight" "fac025_Weight" "fac4_Weight" "renorm025_Weight" "renorm4_Weight" "qsf025_Weight" "qsf4_Weight"; do
  #for syst_weight in "ckkw15_Weight" "ckkw30_Weight"; do
  #for syst_weight in "fac025_Weight" "fac4_Weight"; do
  #for syst_weight in "renorm025_Weight" "renorm4_Weight"; do
  #for syst_weight in "qsf025_Weight" "qsf4_Weight"; do
  #for syst_weight in "weight_WZ_CT14nnlo" "weight_WZ_MMHT2014nnlo" "weight_WZ_NNPDF_down" "weight_WZ_NNPDF_up" "weight_WZ_alpha_s_down" "weight_WZ_alpha_s_up"; do
  for syst_weight in "weight_WZ_alpha_s_down" "weight_WZ_alpha_s_up"; do
  #for syst_weight in "weight_WZ_CT14nnlo" "weight_WZ_MMHT2014nnlo"; do
  #for syst_weight in "weight_WZ_NNPDF_down" "weight_WZ_NNPDF_up"; do
  
    echo "Weight: "$event_weight_syst"*"$syst_weight
  
    python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight_syst}"*"${syst_weight} --filters filters/filters_loose.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${out_tag}/${cuts_tag}${filter}_${syst_weight}/ ${ntuple_path}/${tag}/*${did}*.${suffix}* &
  
  done;

done <${dids_to_process}
