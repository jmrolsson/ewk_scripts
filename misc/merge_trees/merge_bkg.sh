tag="EWKqqbb.2.4.37-0"
ntuple_path=/data/pool1/jolsson/EWK/ewk_mbj_ntuples/
output_path=/share/t3data2/jolsson/EWK/ewk_mbj_ntuples/histfitter/${tag}/

FAIL=0

for bkg in ttbar topEW singletop dijet diboson Z_sherpa_220 W_sherpa_220 #Z_sherpa_221 W_sherpa_221
do
  python mergeTrees.py ${ntuple_path}/${tag}/*.merged --filters filters/filters_ht.json --weights weights_qqbb.json --did-to-group did_to_group.json --output-suffix _${tag}_${bkg} --groups-bkg ${bkg} --groups-sig "" --do-jms-fix --output-path ${output_path} --dids `cat processes/*.list | tr '\n' ' '` > ${bkg}.log 2>&1 &
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


# merge W_sherpa and Z_sherpa together
#hadd -f Bkg_${tag}_WZ.root Bkg_${tag}_*sherpa.root
#rm Bkg_${tag}_*sherpa.root

# Run W/Z reweighting
#svn export --force svn+ssh://svn.cern.ch/reps/atlasoff/PhysicsAnalysis/SUSYPhys/SUSYTools/trunk/scripts/AddZJetsWeights.py
#patch -p0 AddZJetsWeights.py < AddZJetsWeights.patch
#python AddZJetsWeights.py Bkg_${tag}_WZ.root
