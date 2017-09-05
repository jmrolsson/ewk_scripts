#! /usr/bin/env python

import os
import json
import numpy as np
from root_numpy import tree2array
from ROOT import TFile, TChain

path = '/Users/joakim/ewk/ewk_mbj_ntuples/histfitter/2.4.37-0/'
filename = 'condor_Wt_HT500_407018_407020.merged'
tc = TChain('nominal')
tc.Add(os.path.join(path, filename))

def sum_dict(d, keys):
    s = 0.
    for k in keys:
        try:
            s += d[k]
        except KeyError:
            None
    return s

with open('signal_regions_single_bin.json') as json_file:
    signal_regions = json.load(json_file)

for region, selection in signal_regions.iteritems():
    wt_decay_type = tree2array(tc, branches='wt_decay_type', selection=selection)
    unique, counts = np.unique(wt_decay_type, return_counts=True)
    entries = len(wt_decay_type)
    wt = dict(zip(unique,counts/float(entries)))

    print '\n----> Region: {}'.format(region)

    print '\nNumber of events in {}: {}'.format(region ,entries)

    ratio_allhad = sum_dict(wt, [-999])
    print '\nFraction all hadronic (W->qq, t->bW->bqq): {}'.format(ratio_allhad)

    ratio_dilept = sum_dict(wt, range(0, 6))
    print 'Fraction fully-leptonic (W->lnu, t->bW->blnu): {}'.format(ratio_dilept)

    ratio_semilept = sum_dict(wt, range(6, 18))
    print 'Fraction semi-leptonic (W->lnu, t->bW->bqq OR W->qq, t->bW->blnu): {}'.format(ratio_semilept)

    ratio_emu_dilept = 0
    ratio_tau_dilept = 0
    if (ratio_dilept > 0):
        ratio_emu_dilept = sum_dict(wt, [0, 1, 3]) / ratio_dilept
        ratio_tau_dilept = sum_dict(wt, [2, 4, 5]) / ratio_dilept
    print '\nFully-leptonic:'
    print '    (enu enu + enu munu + munu munu) / (all fully-lept): {}'.format( ratio_emu_dilept )
    print '    (enu taunu + munu taunu + taunu taunu) / (all fully-lept): {}'.format( ratio_tau_dilept )

    ratio_emu_semilept = 0
    ratio_tau_semilept = 0
    if (ratio_semilept > 0):
        ratio_emu_semilept = sum_dict(wt, range(6, 14)) / ratio_semilept
        ratio_tau_semilept = sum_dict(wt, range(14, 18)) / ratio_semilept
    print '\nSemi-leptonic:'
    print '      (elnu had + munu had) / (all semi-lept): {}'.format( ratio_emu_semilept )
    print '      (taunu had) / (all semi-lept): {}'.format( ratio_tau_semilept )

    print '\n Fraction of events with fully-leptonic decays and at least one tau in the final state: {}'.format(ratio_tau_dilept*ratio_dilept)
    print '\n Fraction of events with semi-leptonic decays and at least one tau in the final state: {}'.format(ratio_tau_semilept*ratio_semilept)
    print '\n Fraction of total events with at least one tau in the final state: {}'.format(ratio_tau_dilept*ratio_dilept + ratio_tau_semilept*ratio_semilept)
    print '\n Fraction of events with at least one tau among events with leptons: {}'.format((ratio_tau_dilept*ratio_dilept + ratio_tau_semilept*ratio_semilept)/(ratio_dilept+ratio_semilept))


    # decay type
    # -999 had had
    # 0    elnu elnu
    # 1    elnu munu
    # 2    elnu taunu
    # 3    munu munu
    # 4    munu taunu
    # 5    taunu taunu
    # 6    elnu ud
    # 7    elnu cs
    # 8    elnu cd
    # 9    elnu us
    # 10   munu ud
    # 11   munu cs
    # 12   munu cd
    # 13   munu us
    # 14   taunu ud
    # 15   taunu cs
    # 16   taunu cd
    # 17   taunu us
