#!/bin/bash

#tag="tagEWKqqbb.2.4.37-0-merged-filter"
#out_tag="tagEWKqqbb.2.4.37-0-histograms"
tag="tagEWKqqbb.2.4.37-0-merged-nofilter"
out_tag="tagEWKqqbb.2.4.37-0-histograms-noloosefilter"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples

cuts_tag=_January25

echo "----> Data"
tag="tagEWKqqbb.2.4.37-0-merged-nofilter"
for period in periodA.data_2016 periodB.data_2016 periodC.data_2016 periodD.data_2015 periodD.data_2016 periodE.data_2015 periodE.data_2016 periodF.data_2015 periodF.data_2016 periodG.data_2015 periodG.data_2016 periodH.data_2015 periodI.data_2016 periodJ.data_2015 periodK.data_2016 periodL.data_2016; do
  echo "Processing: ${period}"
  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_qqbb_hf_cutflow_check_data${cuts_tag}.json --out_tdirectory hists --treename nominal --newOutputs --copyMBJCutflow --doData -o ${ntuple_path}/${out_tag}/hf_cutflow_check_data${cuts_tag}/ ${ntuple_path}/${tag}/*${period}*.merged &
done;
