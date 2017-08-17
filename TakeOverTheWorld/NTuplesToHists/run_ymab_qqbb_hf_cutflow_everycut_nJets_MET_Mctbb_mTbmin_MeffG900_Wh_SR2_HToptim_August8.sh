#!/bin/bash

tag="2.4.28-0-1-77-gd12fe93"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter 

cuts_tag=hf_cutflow_everycut_nJets_MET_Mctbb_mTbmin_MeffG900_Wh_SR2_HToptim_August8

while read did; do
  echo Processing: ${did}

  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/histograms/hf_cutflow_${cuts_tag}/ ${ntuple_path}/${tag}/*${did}*.merged &

done <dids_to_process_HT_incl_filter.txt
