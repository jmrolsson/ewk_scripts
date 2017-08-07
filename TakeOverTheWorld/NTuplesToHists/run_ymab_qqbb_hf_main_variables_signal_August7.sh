#!/bin/bash

tag="2.4.28-0-1-77-gd12fe93"
# ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter

#while read did; do
# echo Processing: ${did}
#
# python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC_July29.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/histograms/hf_main_variables_dataMC_July29/ ${ntuple_path}/${tag}/*${did}*.merged &
#
#done <dids_to_process_HT_incl_filter.txt

#python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC_July29.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/histograms/hf_main_variables_signal_only/ ${ntuple_path}/${tag}/*C1N2_Wh*.merged

# python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC_July29.json --out_tdirectory hists --treename nominal --newOutputs --copyMBJCutflow --doData -o ${ntuple_path}/histograms/hf_main_variables_dataMC_July29/ ${ntuple_path}/${tag}/*period*data*.merged &

#  for period in periodA.data_2016 periodB.data_2016 periodC.data_2016 periodD.data_2015 periodD.data_2016 periodE.data_2015 periodE.data_2016 periodF.data_2015 periodF.data_2016 periodG.data_2015 periodG.data_2016 periodH.data_2015 periodI.data_2016 periodJ.data_2015 periodK.data_2016 periodL.data_2016; do
#    echo Processing: ${period}
#    python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_dataMC_July29.json --out_tdirectory hists --treename nominal --newOutputs --copyMBJCutflow --doData -o ${ntuple_path}/histograms/hf_main_variables_dataMC_July29_new/ ${ntuple_path}/${tag}/*${period}*.merged &
#  done;


python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_main_variables_signal_August7.json --out_tdirectory hists --treename nominal --eventWeight weight_mc --filters filters/filters_ht.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/histograms/hf_main_variables_signal_August7/ ${ntuple_path}/${tag}/*C1N2_Wh*.merged
