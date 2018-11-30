#! /usr/bin/env/ python
from __future__ import print_function
import argparse
import json
import os

def print_table_begin(f):
    print(r'\begin{table}[h]', file=f)
    print(r'\footnotesize', file=f)
    print(r'\begin{center}\renewcommand\arraystretch{1.6}', file=f)
    print(r'\sisetup{round-mode=figures, round-precision=2,', file=f)
    print(r'retain-explicit-plus=false, group-digits = false}', file=f)
    print(r'\begin{tabular}{|l|l|c|', file=f)
    print(r'S[table-parse-only, round-precision=4]|', file=f)
    print(r'S[table-parse-only, round-precision=3]|', file=f)
    print(r'S[table-parse-only, round-precision=3]|', file=f)
    print(r'S[table-parse-only, round-precision=3]|', file=f)
    print(r'}', file=f)
    print(r'\toprule', file=f)
    print(r'Generator & Fiducial Region & {DSID} & {\begin{tabular}[c]{@{}c@{}}No. of\\events\end{tabular}} & {\begin{tabular}[c]{@{}c@{}}$\sigma \times \epsilon_\textnormal{filter}$\\ $[$pb$]$\end{tabular}} & {$k$-factor} & {$\mathcal{L}_{\mathrm{generated}}~[\mathrm{fb}^{-1}]$}\\', file=f)
    print(r'\midrule', file=f)

def print_table_end(f, group, tag, extra='', nevents_tot = 0, genlumi_tot = 0):
    print(r'\bottomrule', file=f)
    print(r'\end{tabular}', file=f)
    print('\\caption{{The {0:s} MC samples used{1:s}. Total generated number of events (luminosity): {2:.2f} ({3:.2f}$~\mathrm{{fb}}^{{-1}}$).}}'.format(tag, extra, nevents_tot, genlumi_tot), file=f)
    print('\\label{{tab:app:datamc{}}}'.format(group), file=f)
    print(r'\end{center}', file=f)
    print(r'\end{table}', file=f)

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Make cutflow tables from analysis sample metadata (Author: Joakim Olsson)')

    parser.add_argument('-v','--verbose', dest='verbose', action='count', default=0, help='Enable verbose output of various levels. Use --debug to enable output for debugging.')
    parser.add_argument('--debug', dest='debug', action='store_true', help='Enable ROOT output and full-on debugging. Use this if you need to debug the application.')
    parser.add_argument('--weights', required=False, type=str, dest='weights_file', metavar='<file.json>', help='json file specifying the weights by dataset id', default='weights.json')
    parser.add_argument('--dids', metavar='did', type=str, nargs='+', help='DIDs to use or not use (see --blacklist-dids)', default=[])
    parser.add_argument('--blacklist-dids', action='store_true', help='If enabled, the specified DIDs will be skipped')
    parser.add_argument('--did-metadata', required=False, type=str, dest='did_metadata', metavar='did_metadata.json', help='JSON dictionary mapping DID to metadata.', default='did_metadata.json')
    parser.add_argument('--output-prefix', required=False, type=str, dest='output_prefix', help='Output file prefix', default='table_samples')
    parser.add_argument('--output-path', required=False, type=str, dest='output_path', help='Output path', default='./')

    args = parser.parse_args()

    try:

        weights = json.load(file(args.weights_file))
        did_metadata = json.load(file(args.did_metadata))

        # Collect the sample metadata
        table_data = {}
        checked_dids = []
        for did in args.dids:
            if did in checked_dids: continue
            if bool(did in args.dids) == bool(args.blacklist_dids): continue
            checked_dids.append(did)
            try:
                #group = did_metadata[did][0]
                group = did_metadata[did][1]
            except KeyError:
                print('ERROR: dataset {} is not associated with a group, check {}'.format(did, args.did_metadata))
                exit(1)
            try:
                tmp = weights[did]
                tmp['tag'] = did_metadata[did][2]
                tmp['generator'] = did_metadata[did][3]
                tmp['fiducial'] = did_metadata[did][4]
            except KeyError:
                print('ERROR: dataset {} does not have sample weight info, check {}'.format(did, args.weights))
                exit(1)
            try:
                table_data[group][did] = tmp
            except KeyError:
                table_data[group] = {did: tmp}

        # Save latex tables
        for group, metadata in table_data.iteritems():
            try:
                output = os.path.join(args.output_path, '{}_{}.tex'.format(args.output_prefix, group))

                with open(output, 'w') as f:
                    print_table_begin(f)
                    ordered_dids = sorted(metadata.keys())
                    page_i = 0
                    nevents_tot = 0
                    genlumi_tot = 0
                    for i,did in enumerate(ordered_dids):
                        if (i>0 and i%25==0):
                            if (page_i>0):
                                print_table_end(f, group, metadata[did]['tag'], ' (continued)')
                            else:
                                print_table_end(f, group, metadata[did]['tag'])
                            print_table_begin(f)
                            page_i += 1
                        generator = metadata[did]['generator']
                        fiducial = metadata[did]['fiducial']
                        nevents = metadata[did]['num events']
                        xsec = metadata[did]['cross section']
                        eff = metadata[did]['filter efficiency']
                        kfactor = metadata[did]['k-factor']
                        xsec_filtereff = float(xsec)*float(eff)
                        denom = (xsec_filtereff*float(kfactor))
                        if denom > 0:
                          genlumi = nevents / denom / 1000
                        else:
                          genlumi = 0
                        nevents_tot += nevents
                        genlumi_tot += genlumi
                        print('{0:s} & {1:s} & {2:s} & {3:} & {4:} & {5:} & {6:} \\\\'.format(generator, fiducial, did, nevents, xsec_filtereff, kfactor, genlumi), file=f)

                    if (page_i>0):
                        print_table_end(f, group, metadata[did]['tag'], ' (continued)', nevents_tot, genlumi_tot)
                    else:
                        print_table_end(f, group, metadata[did]['tag'], '', nevents_tot, genlumi_tot)
                    nevents_tot = 0
                    genlumi_tot = 0


            except IOError:
                print('ERROR: Could not crate output file {}'.format(output))

    except Exception, e:

        print("An exception was caught!")
