#tag=Wh_SR_CR_VR_September12_HT_incl_filter
#tag=Wh_SR_CR_VR_September15_HT_incl_filter
#tag=Wh_SR_CR_VR_September30_HT_incl_filter
#tag=Wh_SR_CR_VR_October18_HT_incl_filter
tag=Wh_SR_CR_VR_October18_HT_incl_filter_official_signal
for s in $(ls cutflow_resolved/cutflow_${tag}/*.json | grep $1); do python pie_plots.py --input ${s}; done;
