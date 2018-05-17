#!/bin/bash

tag="tagEWKqqbb.2.4.37-0-merged-nofilter"
out_tag="tagEWKqqbb.2.4.37-0-histograms-filter-check"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples
suffix=merged
cuts_tag=_December4

event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2"

echo "----> Processing HT filtered samples"
while read did; do
  echo "Processing: ${did}"

  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_check_HT_MET_filters${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_ht_noloosefilter.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${out_tag}/hf_main_variables_dataMC${cuts_tag}_HT_incl_filter_check/ ${ntuple_path}/${tag}/*${did}*.${suffix}* &

done <dids_to_process_HT_incl_filter_check.txt

echo "----> Processing MET filtered samples"
while read did; do
  echo "Processing: ${did}"

  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_check_HT_MET_filters${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_met_noloosefilter.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${out_tag}/hf_main_variables_dataMC${cuts_tag}_MET_incl_filter_check/ ${ntuple_path}/${tag}/*${did}*.${suffix}* &

done <dids_to_process_MET_incl_filter_check.txt
