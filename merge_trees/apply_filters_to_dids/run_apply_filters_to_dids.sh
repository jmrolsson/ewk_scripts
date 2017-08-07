#!/bin/bash

tag="2.4.28-0-1-77-gd12fe93"
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter

# HT filters
python apply_filters_to_dids.py ${ntuple_path}/${tag}/*.merged --filters ../filters/filters_ht.json --trees nominal --dids $(cat dids_ht_filter.txt | xargs) --output-suffix _ht_filter.merged -o ${ntuple_path}/${tag}/

# MET filters
python apply_filters_to_dids.py ${ntuple_path}/${tag}/*.merged --filters ../filters/filters_met.json --trees nominal --dids $(cat dids_met_filter.txt | xargs) --output-suffix _met_filter.merged -o ${ntuple_path}/${tag}/
