tag="2.4.33-0-1-309-g0817ba7p"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter

python mergeTrees.py ${ntuple_path}/${tag}/*period*.merged --filters filters/filters_ht.json --weights weights_qqbb.json --did-to-group did_to_group.json --output-suffix _${tag} --groups-bkg "" --groups-sig "" --do-jms-fix --do-data
