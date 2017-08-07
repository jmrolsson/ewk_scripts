#!/bin/bash

tag="2.4.28-0-1-77-gd12fe93"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter 
masspoint=300_0

while read did; do
  echo Processing: ${did}
    python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_cutflow_everycut_nJets_MET_Meff_Mctbb_mTbmin_Wh_${masspoint}_HToptim_July19.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/histograms/hf_cutflow_everycut_nJets_MET_Meff_Mctbb_mTbmin_Wh_${masspoint}_HToptim_July19/ ${ntuple_path}/${tag}/*${did}*.merged &
done <dids_to_process_HT_incl_filter.txt
