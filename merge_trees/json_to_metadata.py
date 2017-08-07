# requires weights.json and did_to_group.json in the directory
# produces a metadata-like file with all the information needed mostly

import json

weights = json.load(file('weights.json'))
did_to_group = json.load(file('did_to_group.json'))

header = '''id/I:name/C:xsec/F:kfac/F:eff/F:relunc/F
# cross-sections are in pb

# DSID  Physics short                               xsec    k-fac   eff     rel. unc.

##########################################################################################################################
'''

with open('weights.meta', 'w+') as f:
  print >>f, header
  for did, data in iter(sorted(weights.iteritems())):
    print >>f, ('{0:6s}\t{1:<20s}\t{2:10.10f}\t{3:16.4f}\t{4:16.4f}\t{5:14.6f}'.format(did,
                           did_to_group.get(did),
                           data['cross section'],
                           data['k-factor'],
                           data['filter efficiency'],
                           data['rel uncert']))
