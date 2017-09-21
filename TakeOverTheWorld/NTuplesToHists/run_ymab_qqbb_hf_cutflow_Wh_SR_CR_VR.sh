#!/bin/bash

#tag="2.4.28-0-1-77-gd12fe93"
#ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter

tag="2.4.37-0-5-g6d1fba4"
ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples

#cuts_tag=hf_cutflow_Wh_SR_CR_VR_August14
#cuts_tag=hf_cutflow_Wh_SR_CR_VR_August15
#cuts_tag=hf_cutflow_Wh_SR_CR_VR_August20
#cuts_tag=hf_cutflow_only_Wh_CR_test_singletop_August22
#cuts_tag=hf_cutflow_Wh_SR_CR_VR_September12
cuts_tag=hf_cutflow_Wh_SR_CR_VR_minimal_September15

while read did; do
  echo Processing: ${did}

  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${tag}-histograms/${cuts_tag}/ ${ntuple_path}/${tag}/*${did}*.merged &

done <dids_to_process_HT_incl_filter.txt
