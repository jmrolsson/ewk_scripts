#!/bin/bash

tag="tagEWKqqbb.2.4.37-0-merged-filter"
out_tag="tagEWKqqbb.2.4.37-0-histograms"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples

filter=_HT_incl_filter
#filter=_MET_incl_filter

suffix=merged

cuts_tag=_September27
#cuts_tag=_singletop_CR_VR_September27
#cuts_tag=_ttbar_CR_VR_September27
#cuts_tag=_Zjets_CR_VR_September27

event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2"

dids_to_process=dids_to_process$filter.txt
echo "----> MC"
while read did; do
 echo "Processing: ${did}"

 python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${tag}-histograms/hf_main_variables_dataMC${cuts_tag}${filter}/ ${ntuple_path}/${tag}/*${did}*.${suffix} &

done <${dids_to_process}

# echo "----> Data"
# for period in periodA.data_2016 periodB.data_2016 periodC.data_2016 periodD.data_2015 periodD.data_2016 periodE.data_2015 periodE.data_2016 periodF.data_2015 periodF.data_2016 periodG.data_2015 periodG.data_2016 periodH.data_2015 periodI.data_2016 periodJ.data_2015 periodK.data_2016 periodL.data_2016; do
#   echo "Processing: ${period}"
#   python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC${cuts_tag}.json --out_tdirectory hists --treename nominal --newOutputs --copyMBJCutflow --doData -o ${ntuple_path}/${tag}-histograms/hf_main_variables_dataMC${cuts_tag}${filter}/ ${ntuple_path}/${tag}/*${period}*.merged &
# done;
