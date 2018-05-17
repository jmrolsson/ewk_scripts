#!/bin/bash

ntuple_path=/share/t3data2/jolsson/EWK/ewk_simpleanalysis
#ntuple_path=/Users/joakim/ewk/ewk_simpleanalysis

pattern="20180202"

#cuts_tag=_January24
#cuts_tag=_additional_January30
#cuts_tag=_February1
#cuts_tag=_February2_cutflow
#cuts_tag=_February2_bareminimum
#cuts_tag=_February5_cutflow
#cuts_tag=_February5
#cuts_tag=_February9_1or2L
cuts_tag=_February9_1L
#event_weight="mc_weight"
#pattern="user.jolsson.*.simple_singletop.*"
#pattern="user.jolsson.*.simple_ttbar.*"


## for WWbb (all mc_weight==1)
event_weight="1.0"
#pattern="user.jolsson.4073.*.simple_singletop_syst"
pattern"user.jolsson.4073*.simple_WWbbDR_syst.*20180227"

#for dir in "user.jolsson.410250.simple_ttbar_syst.EwkWhAllHad2016.20180202" "user.jolsson.410251.simple_ttbar_syst.EwkWhAllHad2016.20180202"; do
#for dir in "user.jolsson.410099.simple_singletop_syst.EwkWhAllHad2016.20180202" "user.jolsson.410145.simple_singletop_syst.EwkWhAllHad2016.20180208" "user.jolsson.410146.simple_singletop_syst.EwkWhAllHad2016.20180208" "user.jolsson.410164.simple_singletop_syst.e4857_p2949.EwkWhAllHad2016.20180208" "user.jolsson.410164.simple_singletop_syst.e4857_p3135.EwkWhAllHad2016.20180208"; do
#for dir in "user.jolsson.410100.simple_singletop_syst.EwkWhAllHad2016.20180202"; do
for dir in $(ls ${ntuple_path} | grep ${pattern}); do
  echo ${ntuple_path}/$dir

  #python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_simpleanalysis_syst${cuts_tag}.json --treename EwkWhAllHad2016__ntuple --eventWeight ${event_weight} --newOutputs -o ${ntuple_path}/hists_simpleanalysis${cuts_tag}/ ${ntuple_path}/${dir}/*.root &
  python YourMacrosAreBadAndYouShouldFeelBad.py --config config/config_simpleanalysis_syst${cuts_tag}.json --treename EwkWhAllHad2016__ntuple --eventWeight ${event_weight} --newOutputs -o ${ntuple_path}/hists_simpleanalysis${cuts_tag}_eventWeightEq1/ ${ntuple_path}/${dir}/*.root &

done;
