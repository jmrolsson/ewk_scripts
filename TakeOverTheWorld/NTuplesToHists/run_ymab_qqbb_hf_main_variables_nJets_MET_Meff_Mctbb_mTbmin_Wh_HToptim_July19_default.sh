#!/bin/bash

tag="2.4.28-0-1-77-gd12fe93"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter

while read did; do
  echo Processing: ${did}

  # python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_nJets_MET_Meff_Mctbb_mTbmin_Wh_HToptim_July19_default.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/histograms/hf_main_variables_nJets_MET_Meff_Mctbb_mTbmin_Wh_HToptim_July19_default/ ${ntuple_path}/${tag}/*${did}*.merged &
  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_nJets_MET_Meff_Mctbb_mTbmin_Wh_HToptim_July19_default_dphi_sum4jet.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/histograms/hf_main_variables_nJets_MET_Meff_Mctbb_mTbmin_Wh_HToptim_July19_default_dphi_sum4jet/ ${ntuple_path}/${tag}/*${did}*.merged &

done <dids_to_process_HT_incl_filter.txt
