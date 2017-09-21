#tag=Wh_SR_CR_VR_September12
tag=Wh_SR_CR_VR_minimal_September15
sample=_HT_incl_filter
for s in $(ls cutflow_resolved/cutflow_${tag}${sample}/*.json); do python pie_plots.py --input ${s}; done;
