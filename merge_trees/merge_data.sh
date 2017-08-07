tag="2.4.28-0-1-77-gd12fe93"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter

python mergeTrees.py ${ntuple_path}/${tag}/*period*.merged --tree nominal --filters filters/filters_ht.json --weights weights_qqbb.json --did-to-group did_to_group.json --output-suffix _${tag} --groups-bkg "" --groups-sig "" --do-data
