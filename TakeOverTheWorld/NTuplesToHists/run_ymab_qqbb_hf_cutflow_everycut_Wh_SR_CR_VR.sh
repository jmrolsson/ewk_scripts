#!/bin/bash

#tag="tag2.4.37-0-5-g6d1fba4"
#out_tag="tag2.4.37-0-5-g6d1fba4-histograms-noweights"
#tag="tag2.4.37-0-5-g6d1fba4-merged-nofilter"
#out_tag="tag2.4.37-0-5-g6d1fba4-histograms-allevents"
#ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples

#tag="tagEWKqqbb.2.4.37-0-merged-filter"
#out_tag="tagEWKqqbb.2.4.37-0-histograms-noloosefilter-noweights"

tag="tagEWKqqbb.2.4.37-0-merged-nofilter"
out_tag="tagEWKqqbb.2.4.37-0-histograms-noloosefilter"
#tag="tagEWKqqbb.2.4.42-merged-nofilter"
#out_tag="tagEWKqqbb.2.4.42-histograms-noloosefilter"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples

#filter=_HT_incl_filter
filter=_MET_incl_filter

#filter=_HT_filter_only
#filter=_MET_filter_only
#filter=_sherpa_220_only

suffix=merged

#cuts_tag=hf_cutflow_everycut_Wh_SR_CR_VR_October31
#cuts_tag=hf_cutflow_everycut_Wh_SR_CR_VR_November16
cuts_tag=hf_cutflow_everycut_Wh_SR_20180920

#event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2"
event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2*weight_pu"

# event_weight="1.0"

dids_to_process=dids_to_process$filter.txt
while read did; do
 echo Processing: ${did}

 #python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_ht_noloosefilter.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${out_tag}/${cuts_tag}${filter}/ ${ntuple_path}/${tag}/*${did}*.${suffix}* > log_${cuts_tag}${filter}_${did}.txt &
 python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_met_noloosefilter.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${out_tag}/${cuts_tag}${filter}/ ${ntuple_path}/${tag}/*${did}*.${suffix}* > log_${cuts_tag}${filter}_${did}.txt &

done <${dids_to_process}
