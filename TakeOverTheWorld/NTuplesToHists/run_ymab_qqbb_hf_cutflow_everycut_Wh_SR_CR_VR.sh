#!/bin/bash

#tag="2.4.28-0-1-77-gd12fe93"
#ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
#dids_to_process=dids_to_process_HT_incl_filter.txt
#suffix=merged

#tag="2.4.37-0-5-g6d1fba4"
#ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples
#dids_to_process=dids_to_process_HT_incl_filter.txt
#suffix=merged

tag="2.4.33-5-0-52-g169a7c2-mCTbb-MEV"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
dids_to_process=dids_to_process_HT_incl_filter_mCTbbMEV.txt
suffix=root

cuts_tag=hf_cutflow_everycut_Wh_SR_CR_VR_October31

event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2"

filter=_HT_incl_filter

while read did; do
  echo Processing: ${did}

  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${tag}-histograms/${cuts_tag}${filter}/ ${ntuple_path}/${tag}/*${did}*.${suffix} &

done <${dids_to_process}
