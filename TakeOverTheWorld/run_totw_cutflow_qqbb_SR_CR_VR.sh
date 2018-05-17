#python totw_cutflow.py -b --config config/config_totw_qqbb_hf_cutflow_Wh_SR_CR_VR_November16_HT_incl_filter.yml --weights weights_qqbb.json -i hists --type summary --lumi 36.1 --latex --external-caption --json --debug
#python totw_cutflow.py -b --config config/config_totw_qqbb_hf_cutflow_Wh_SR_CR_VR_November16_MET_incl_filter.yml --weights weights_qqbb.json -i hists --type summary --lumi 36.1 --latex --external-caption --json --debug
python totw_cutflow.py -b --config config/config_totw_qqbb_hf_cutflow_Wh_SR_CR_VR_November16_MET_incl_filter_pu.yml --weights weights_qqbb.json -i hists --type summary --lumi 36.1 --latex --external-caption --json --debug

#python totw_cutflow.py -b --config config/config_totw_qqbb_hf_cutflow_Wh_SR_CR_VR_November16_sherpa_220_only.yml --weights weights_qqbb.json -i hists --type summary --lumi 36.1 --latex --external-caption --json --debug
