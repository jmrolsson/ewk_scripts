#!/bin/bash

tag="tagEWKqqbb.2.4.37-0-merged-filter"
out_tag="tagEWKqqbb.2.4.37-0-histograms"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples

suffix=merged

cuts_tag=_Nm1_EWKqqbb

event_weight="weight_mc*weight_btag*weight_elec*weight_muon*weight_jvt*weight_WZ_2_2*weight_pu"


dids_to_process=dids_to_process_signal.txt
echo "----> Processing signal samples only"
while read did; do
  echo "Processing: ${did}"

  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config${cuts_tag}.json --out_tdirectory hists --treename nominal --eventWeight ${event_weight} --filters filters/filters_loose.json --newOutputs --copyMBJCutflow -o ${ntuple_path}/${out_tag}/hf${cuts_tag}/ ${ntuple_path}/${tag}/*${did}*.${suffix}* &

done <${dids_to_process}
