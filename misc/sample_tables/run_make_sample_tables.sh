#!/usr/bin/env bash

for group in singletop ttbar topEW Z_sherpa_220 W_sherpa_220 diboson dijet; 
do
 python make_sample_tables.py --weights weights_qqbb.json --did-metadata did_metadata.json --dids $(cat processes/${group}.list) -vvv
done

# # signal
# python make_signal_tables.py --weights weights_qqbb.json --did-metadata did_metadata.json --dids $(cat processes/Wh.list) -vvv
