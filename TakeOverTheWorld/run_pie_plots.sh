tag=Wh_SR_CR_VR_August15
sample=_HT_incl_filter
for s in $(ls cutflow_resolved/cutflow_${tag}${sample}/*.json); do python pie_plots.py --input ${s}; done;
