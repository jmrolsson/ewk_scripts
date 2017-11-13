#!/bin/bash

#tag="2.4.28-0-1-77-gd12fe93"
#ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
#dids_to_process=dids_to_process_HT_incl_filter.txt
#suffix=merged

tag="2.4.37-0-5-g6d1fba4"
ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples
dids_to_process=dids_to_process_HT_incl_filter.txt
suffix=merged

# tag="2.4.33-5-0-52-g169a7c2-mCTbb-MEV"
# ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# dids_to_process=dids_to_process_HT_incl_filter_mCTbbMEV.txt
# suffix=root

cuts_tag=bkgdComposition_November10
#cuts_tag=Nm1_SR1_November10
#cuts_tag=Nm1_SR3_November10

event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2"

filter=_HT_incl_filter

echo "----> MC"
while read did; do
 echo "Processing: ${did}"

 python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${tag}-histograms/hf_${cuts_tag}${filter}/ ${ntuple_path}/${tag}/*${did}*.${suffix} &

done <${dids_to_process}

# echo "----> Data"
# for period in periodA.data_2016 periodB.data_2016 periodC.data_2016 periodD.data_2015 periodD.data_2016 periodE.data_2015 periodE.data_2016 periodF.data_2015 periodF.data_2016 periodG.data_2015 periodG.data_2016 periodH.data_2015 periodI.data_2016 periodJ.data_2015 periodK.data_2016 periodL.data_2016; do
#   echo "Processing: ${period}"
#   python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_${cuts_tag}.json --out_tdirectory hists --treename nominal --newOutputs --copyMBJCutflow --doData -o ${ntuple_path}/${tag}-histograms/hf_${cuts_tag}${filter}/ ${ntuple_path}/${tag}/*${period}*.merged &
# done;
