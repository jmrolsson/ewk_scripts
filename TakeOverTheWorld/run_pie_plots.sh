#tag=Wh_SR_CR_VR_November16_HT_incl_filter
#tag=Wh_SR_CR_VR_November16_MET_incl_filter
tag=Wh_SR_CR_VR_November16_MET_incl_filter_pu
#tag=Wh_SR_CR_VR_January16_MET_incl_filter
#tag=Wh_SR_CR_VR_January18_MET_incl_filter
for s in $(ls cutflow_resolved/cutflow_${tag}/*.json | grep $1); do python pie_plots.py --input ${s} --config config_common.json; done;
