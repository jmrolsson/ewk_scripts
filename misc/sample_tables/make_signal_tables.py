#! /usr/bin/env/ python
from __future__ import print_function
import argparse
import json
import os

def print_table_begin(f):
    print(r'\begin{table}[h]', file=f)
    print(r'\footnotesize', file=f)
    print(r'\begin{center}\renewcommand\arraystretch{1.6}', file=f)
    print(r'\begin{tabular}{|l|c|c|c|}', file=f)
    print(r'\toprule', file=f)
    print(r'$(\mheavy, \mneut)~[\gev]$ & DSID & $\sigma_{\chipm,\neuttwo} \pm \delta \sigma_{\chipm,\neuttwo}$ & $\left(\sigma_{\chipm,\neuttwo} \pm \delta \sigma_{\chipm,\neuttwo}\right)\times\mathrm{BR}_{W}\times\mathrm{BR}_{h}$ \\', file=f)
    print(r'\midrule', file=f)

def print_table_end(f):
    print(r'\bottomrule', file=f)
    print(r'\end{tabular}', file=f)
    print('\\caption{Signal sample cross sections and theory uncertainties.}', file=f)
    print('\\label{tab:signal-xsec}', file=f)
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
    parser.add_argument('--output-name', required=False, type=str, dest='output_name', help='Output file prefix', default='table_signal.tex')
    parser.add_argument('--output-path', required=False, type=str, dest='output_path', help='Output path', default='./')

    args = parser.parse_args()

    try:
        with open(os.path.join(args.output_path, args.output_name), 'w') as f:

            print_table_begin(f)

            weights = json.load(file(args.weights_file))

            # Collect the sample metadata
            for did in args.dids:
                if bool(did in args.dids) == bool(args.blacklist_dids): continue
                try:
                    m_c1n2 = weights[did]['m_c1n2']
                    m_n1 = weights[did]['m_n1']
                    xsec = weights[did]['cross section']*1000.
                    xsec_rel_uncert = weights[did]['rel uncert']
                    xsec_uncert = xsec_rel_uncert*xsec

                    # branching ratios for W->qq and h->bb
                    br_w = 0.6741
                    br_h = 0.5820
                    xsec_susy = xsec/br_h/br_w
                    xsec_susy_uncert = xsec_susy*xsec_rel_uncert
                    print('$({:.0f},{:.0f})$ & ${}$ & ${:.1f}\\pm{:.1f}$ & ${:.1f}\\pm{:.1f}~({:.1f}\\%)$ \\\\'.format(m_c1n2, m_n1, did, xsec_susy, xsec_susy_uncert, xsec, xsec_uncert, 100.0*xsec_rel_uncert), file=f)
                except KeyError:
                    print('ERROR: dataset {} does not have sample weight info, check {}'.format(did, args.weights))
                    exit(1)

            print_table_end(f)

    except IOError:
        print('ERROR: Could not crate output file {}'.format(output))
