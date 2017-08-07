#python merge_outputs.py -o ewk_mbj_ntuples/histfitter/ "*/fetch/data-output_histfitter/" *.root
#python merge_outputs.py -o ewk_mbj_ntuples/tree/ "*/fetch/data-output_tree/" *.root
python merge_outputs.py -o ewk_mbj_ntuples/histfitter/ "C1N2_*/data-output_histfitter/" *.root
python merge_outputs.py -o ewk_mbj_ntuples/tree/ "C1N2_*/data-output_tree/" *.root
