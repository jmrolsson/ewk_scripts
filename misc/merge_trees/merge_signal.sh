#tag="2.4.37-0-5-g6d1fba4"
#ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples/
#output_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter/${tag}/

tag="2.4.33-5-0-52-g169a7c2-mCTbb-MEV"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter/${tag}/
output_path=${ntuple_path}

FAIL=0

for sig in Wh
do
 python mergeTrees.py -v ${ntuple_path}/*.root --filters filters/filters_ht.json --weights weights_qqbb.json --did-to-group did_to_group.json --output-suffix _${tag}_${sig} --groups-bkg "" --groups-sig ${sig} --do-jms-fix --output-path ${output_path} --dids `cat processes/${sig}*.list  | tr '\n' ' '` > ${sig}.log 2>&1 &
done

for job in `jobs -p`
do
 echo $job
 wait $job || let "FAIL+=1"
done

if [ "$FAIL" == "0" ];
then
 echo "YAY!"
else
 echo "FAIL! ($FAIL)"
fi
