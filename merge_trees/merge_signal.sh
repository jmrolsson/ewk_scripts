tag="2.4.28-0-1-77-gd12fe93"
ntuple_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter
# ntuple_path=/Users/joakim/ewk/ewk_mbj_ntuples/histfitter

FAIL=0

for sig in Wh WZ 
do
  python mergeTrees.py ${ntuple_path}/${tag}/*.merged --tree nominal --filters filters/filters_ht.json --weights weights_qqbb.json --did-to-group did_to_group.json --output-suffix _${tag}_${sig} --groups-bkg "" --groups-sig ${sig} --dids `cat processes/*.list | tr '\n' ' '` > ${sig}.log 2>&1 &
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
