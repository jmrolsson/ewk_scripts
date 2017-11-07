#!/bin/bash

#tag="2.4.28-0-1-77-gd12fe93"
#tag2=_July29
#tag="2.4.33-0-1-309-g0817ba7p"
#ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
#ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter

tag="2.4.37-0-5-g6d1fba4"
#tag2=_September27
#tag2=_singletop_CR_VR_September27
#tag2=_ttbar_CR_VR_September27
tag2=_Zjets_CR_VR_September27
ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples
event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2"

filter=_HT_incl_filter

while read did; do
 echo Processing: ${did}

 python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC${tag2}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${tag}-histograms/hf_main_variables_dataMC${tag2}${filter}/ ${ntuple_path}/${tag}/*${did}*.merged &

done <dids_to_process_HT_incl_filter.txt

#python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC${tag2}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${tag}-histograms/hf_main_variables_signal_only/ ${ntuple_path}/${tag}/*C1N2_Wh*.merged

# python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC${tag2}.json --out_tdirectory hists --treename nominal --newOutputs --copyMBJCutflow --doData -o ${ntuple_path}/${tag}-histograms/hf_main_variables_dataMC${tag2}${filter}/ ${ntuple_path}/${tag}/*period*data*.merged &

for period in periodA.data_2016 periodB.data_2016 periodC.data_2016 periodD.data_2015 periodD.data_2016 periodE.data_2015 periodE.data_2016 periodF.data_2015 periodF.data_2016 periodG.data_2015 periodG.data_2016 periodH.data_2015 periodI.data_2016 periodJ.data_2015 periodK.data_2016 periodL.data_2016; do
  echo Processing: ${period}
  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC${tag2}.json --out_tdirectory hists --treename nominal --newOutputs --copyMBJCutflow --doData -o ${ntuple_path}/${tag}-histograms/hf_main_variables_dataMC${tag2}${filter}/ ${ntuple_path}/${tag}/*${period}*.merged &
done;
