tag="EWKqqbb.2.4.37-0"
ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples/
output_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter/${tag}/

python mergeTrees.py ${ntuple_path}/${tag}/*period*.merged --filters filters/filters_ht.json --weights weights_qqbb.json --did-to-group did_to_group.json --output-suffix _${tag} --groups-bkg "" --groups-sig "" --do-jms-fix --output-path ${output_path} --do-data > data.log 2>&1 &
