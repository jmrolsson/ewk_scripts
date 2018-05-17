#!/usr/bin/env python

# @file:    totw_cutflow.py
# @purpose: Make professional looking cutflows for different regions
# @author:  Joakim Olsson <joakim.olsson@cern.ch>
# @date:    April 2017
# (derived from Giordon Stark's <gstark@cern.ch> totw.py plotting script )

# __future__ imports must occur at beginning of file
#   print(string, f=fd)
from __future__ import print_function
# used to redirect ROOT output
#   see http://stackoverflow.com/questions/21541238/get-ipython-doesnt-work-in-a-startup-script-for-ipython-ipython-notebook
import tempfile

import os, sys
# grab the stdout and have python write to this instead
# ROOT will write to the original stdout
STDOUT = os.fdopen(os.dup(sys.stdout.fileno()), 'w')

# for logging, set it up
import logging
root_logger = logging.getLogger()
root_logger.addHandler(logging.StreamHandler(STDOUT))
logger = logging.getLogger("totw")

# import all libraries
import argparse
import subprocess
import glob
import yaml
import json
import io

'''
  with tempfile.NamedTemporaryFile() as tmpFile:
    if not args.debug:
      ROOT.gSystem.RedirectOutput(tmpFile.name, "w")

    # execute code here

    if not args.debug:
      ROOT.gROOT.ProcessLine("gSystem->RedirectOutput(0);")
'''

# Set up ROOT
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

#root_numpy
import numpy as np
import root_numpy as rnp
import rootpy as rpy
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as pl
from uncertainties import ufloat
from rootpy.io import root_open
from rootpy.plotting.style import set_style, get_style
from rootpy.plotting import Canvas, Legend, HistStack, Hist, Pad
from rootpy.plotting.hist import _Hist
from palettable import colorbrewer, tableau
from itertools import cycle, chain
import copy
import re

import plotHelpers as ph


class Cut:
  """
  n: number of raw events
  wn: sum of event weights
  wsn: sum of event weights x 'sample scale factors'
  """
  def __init__(self, n=0.0, err=0.0, wn=0.0, werr=0.0, wsn=0.0, wserr=0.0):
    self.n = n
    self.err = err
    self.wn = wn
    self.werr = werr
    self.wsn = wsn
    self.wserr = wserr

  def add(self, n, err, wn, werr, wsn, wserr):
    self.n += n
    self.err = np.sqrt(self.err**2 + err**2)
    self.wn += wn
    self.werr = np.sqrt(self.werr**2 + werr**2)
    self.wsn += wsn
    self.wserr = np.sqrt(self.wserr**2 + wserr**2)

  def add_cut(self, c):
    self.n += c.n
    self.err = np.sqrt(self.err**2 + c.err**2)
    self.wn += c.wn
    self.werr = np.sqrt(self.werr**2 + c.werr**2)
    self.wsn += c.wsn
    self.wserr = np.sqrt(self.wserr**2 + c.wserr**2)

  def reset(self):
    self.n = 0.0
    self.err = 0.0
    self.wn = 0.0
    self.werr = 0.0
    self.wsn = 0.0
    self.wserr = 0.0

  def print_cut(self):
    return "(Cut: n = {:.8f}+/-{:.8f}, wn = {:.8f}+/-{:.8f}, wsn = {:.8f}+/-{:.8f})".format(self.n, self.err, self.wn, self.werr, self.wsn, self.wserr)
  def __str__(self):
    return self.print_cut()
  def __unicode__(self):
    return self.print_cut()
  def __repr__(self):
    return self.print_cut()

def format_arg_value(arg_val):
  """ Return a string representing a (name, value) pair.

  >>> format_arg_value(('x', (1, 2, 3)))
  'x=(1, 2, 3)'
  """
  arg, val = arg_val
  return "%s=%r" % (arg, val)

# http://wordaligned.org/articles/echo
def echo(*echoargs, **echokwargs):
  logger.debug(echoargs)
  logger.debug(echokwargs)
  def echo_wrap(fn):
    """ Echo calls to a function.

    Returns a decorated version of the input function which "echoes" calls
    made to it by writing out the function's name and the arguments it was
    called with.
    """

    # Unpack function's arg count, arg names, arg defaults
    code = fn.func_code
    argcount = code.co_argcount
    argnames = code.co_varnames[:argcount]
    fn_defaults = fn.func_defaults or list()
    argdefs = dict(zip(argnames[-len(fn_defaults):], fn_defaults))

    def wrapped(*v, **k):
      # Collect function arguments by chaining together positional,
      # defaulted, extra positional and keyword arguments.
      positional = map(format_arg_value, zip(argnames, v))
      defaulted = [format_arg_value((a, argdefs[a]))
                   for a in argnames[len(v):] if a not in k]
      nameless = map(repr, v[argcount:])
      keyword = map(format_arg_value, k.items())
      args = positional + defaulted + nameless + keyword
      write("%s(%s)\n" % (fn.__name__, ", ".join(args)))
      return fn(*v, **k)
    return wrapped

  write = echokwargs.get('write', sys.stdout.write)
  if len(echoargs) == 1 and callable(echoargs[0]):
    return echo_wrap(echoargs[0])
  return echo_wrap

#@echo(write=logger.debug)
def do_totw(args):
  pass

def ensure_dir(f):
    d = os.path.dirname(f)
    if not os.path.exists(d):
        os.makedirs(d)

did_regex = re.compile('(\d{6,8})')
def get_did(hist):
  if not isinstance(hist, _Hist):
    import pdb; pdb.set_trace()
    raise TypeError("Must pass in a rootpy Hist object")
  m = did_regex.search(hist.get_directory().GetFile().name)
  if m is None:
    raise ValueError("%s is not a valid filename" % hist.get_directory().GetFile().name)
  return m.groups()[0]

def save_cutflow_summary(cuts_signal, cuts_background, outfile='cutflow.txt', caption='', label='', do_latex=False, ext_caption=False, do_json=False, no_signal=False):

  if do_latex:
    toprule = r"\toprule"
    bottomrule = r"\bottomrule"
    midrule = r"\midrule"
  else:
    toprule = bottomrule = '*' * (190)
    midrule = '-' * (190)

  try:
      ensure_dir(outfile)
      if do_latex:
        f = open(re.sub(".txt", ".tex", outfile), 'w')
        if ext_caption:
          fcap = open(re.sub(".txt", "_caption.tex", outfile), 'w')
      else:
        f = open(outfile, 'w')

      if do_json:
        bkgd_list = []
        sig_list = []

      if do_latex:
        if not ext_caption:
          print(r"\begin{table}[!ht]", file=f)
        print(r"\tiny", file=f)
        print(r"\begin{center}\renewcommand\arraystretch{1.6}", file=f)
        print(r"\sisetup{round-mode=figures, round-precision=2, group-digits = true, separate-uncertainty=true}", file=f)
        print(r"\scalebox{0.68}{", file=f)
        print(r"\begin{tabular}{l | ", file=f)
        print(r"S[round-mode=places]|", file=f)
        print(r"S[scientific-notation = true]|", file=f)
        print(r"S[scientific-notation = true]|", file=f)
        print(r"S|", file=f)
        print(r"S|", file=f)
        print(r"S", file=f)
        print(r"}", file=f)

      # Add background samples

      print(toprule, file=f)
      if do_latex:
        print("\multicolumn{1}{l}{Background} & \multicolumn{1}{c}{$N_B^{\\mathrm{raw}}$} & \multicolumn{1}{c}{$N_B^{\\mathrm{w}}$} & \multicolumn{1}{c}{$N_B$} & \multicolumn{3}{c}{} \\\\", file=f)
      else:
        print("{: <25} | Raw Events              | Weighted Events         | Scaled Events".format('Background'), file=f)
      print(midrule, file=f)

      tot_bkgd = Cut()
      for _, tag, c in cuts_background:
        tot_bkgd.add_cut(c)
        if do_json:
          bkgd_list.append({"label": tag, "nevents_raw": c.n, "err_raw": c.err, "nevents_weighted": c.wn, "err_weighted": c.werr, "nevents": c.wsn, "err": c.wserr})
        if do_latex:
          cutflow_str = "{} & \\num{{{:.0f}}} & \\num{{{:.1uS}}} & \\num{{{:.1uS}}} & \multicolumn{{3}}{{c}}{{}} \\\\".format(
              tag, ufloat(c.n, c.err), ufloat(c.wn, c.werr), ufloat(c.wsn, c.wserr))
          cutflow_str = cutflow_str.replace(r'+/-', r'\pm')
          cutflow_str = re.sub('num{[0\.]*0\\\\pm0}', 'num{0.0\pm0.0}', cutflow_str)
        else:
          cutflow_str = "{: <25} | {:10.2f} +/- {:8.2f} | {:10.2f} +/- {:8.2f} | {:10.2f} +/- {:8.2f}".format(
              tag, c.n, c.err, c.wn, c.werr, c.wsn, c.wserr)
        print(cutflow_str, file=f)
      print(midrule, file=f)
      if do_json:
        tot_bkgd_dict = {"nevents_raw": tot_bkgd.n, "err_raw": tot_bkgd.err,
                        "nevents_weighted": tot_bkgd.wn, "err_weighted": tot_bkgd.werr,
                        "nevents": tot_bkgd.wsn, "err": tot_bkgd.wserr}
      if do_latex:
        cutflow_str = "{} & \\num{{{:.0f}}} & \\num{{{:.1uS}}} & \\num{{{:.1uS}}} & \multicolumn{{3}}{{c}}{{}} \\\\".format(
            'Tot. Background', ufloat(tot_bkgd.n, tot_bkgd.err), ufloat(tot_bkgd.wn, tot_bkgd.werr), ufloat(tot_bkgd.wsn, tot_bkgd.wserr))
        cutflow_str = cutflow_str.replace(r'+/-', r'\pm')
        cutflow_str = re.sub('num{[0\.]*0\\\\pm0}', 'num{0.0\pm0.0}', cutflow_str)
      else:
        cutflow_str = "{: <25} | {:10.2f} +/- {:8.2f} | {:10.2f} +/- {:8.2f} | {:10.2f} +/- {:8.2f}".format(
          'Tot. Background', tot_bkgd.n, tot_bkgd.err, tot_bkgd.wn, tot_bkgd.werr, tot_bkgd.wsn, tot_bkgd.wserr)
      print(cutflow_str, file=f)

      # Add signal samples

      if not no_signal:
        print(midrule, file=f)
        if do_latex:
          print("\multicolumn{1}{c}{$(m_{\\tilde{\\chi}^{\\pm}_{1},\\tilde{\\chi}^{0}_{2}}, m_{\\tilde{\\chi}^{0}_{1}})$} & \multicolumn{1}{c}{$N_S^{\\mathrm{raw}}$} & \multicolumn{1}{c}{$N_S^{\\mathrm{w}}$} & \multicolumn{1}{c}{$N_S$} & \multicolumn{1}{c}{$N_S/N_B~[\\%]$} & \multicolumn{1}{c}{$N_S/\sqrt{N_B}$} & \multicolumn{1}{c}{$\\mathcal{Z}_n$} \\\\", file=f)
        else:
          print("{0: <25} | Raw Events              | Weighted Events         | Scaled Events           | S/B [%]         | S/sqrt(B_tot)   | BinomialExpZ(S,B_tot,0.30)".format('Signal'), file=f)
        print(midrule, file=f)
        for _, tag, c in cuts_signal:
          if tot_bkgd.wsn>0:
            s_over_b = c.wsn/tot_bkgd.wsn
            s_sqrt_b = c.wsn/np.sqrt(tot_bkgd.wsn)
          else:
            s_over_b = 0.
            s_sqrt_b = 0.
          zn = ROOT.RooStats.NumberCountingUtils.BinomialExpZ(c.wsn, tot_bkgd.wsn, 0.3)
          if (zn <0): zn = 0
          if (zn == float('inf')): zn = 0
          if do_json:
            masspoint = map(int, re.findall('\d+', tag))
            if len(masspoint)>1:
              sig_list.append({"label": tag, "m_c1n2": masspoint[0], "m_n1": masspoint[1],
                               "signal_raw": c.n, "err_signal_raw": c.err,
                               "signal_weighted": c.wn, "err_signal_weighted": c.werr,
                               "signal": c.wsn, "err_signal": c.wserr,
                               "bkgd_raw": tot_bkgd.n, "err_bkgd_raw": tot_bkgd.err,
                               "bkgd_weighted": tot_bkgd.wn, "err_bkgd_weigthed": tot_bkgd.werr,
                               "bkgd": tot_bkgd.wsn, "err_bkgd": tot_bkgd.wserr,
                               "ratio": s_over_b, "s_sqrt_b": s_sqrt_b, "significance": zn})
          if do_latex:
            cutflow_str = "{} & \\num{{{:.0f}}} & \\num{{{:.1uS}}} & \\num{{{:.1uS}}} & \\num{{{:g}}} & \\num{{{:g}}} & \\num{{{:g}}} \\\\".format(
              tag, ufloat(c.n, c.err), ufloat(c.wn, c.werr), ufloat(c.wsn, c.wserr), s_over_b*100., s_sqrt_b, zn)
            cutflow_str = cutflow_str.replace(r'+/-', r'\pm')
            cutflow_str = re.sub('num{[0\.]*0\\\\pm0}', 'num{0.0\pm0.0}', cutflow_str)
          else:
            cutflow_str = "{: <25} | {:10.2f} +/- {:8.2f} | {:10.2f} +/- {:8.2f} | {:10.2f} +/- {:8.2f} | {:15.1f} | {:15.3f} | {:10.3f}".format(
              tag, c.n, c.err, c.wn, c.werr, c.wsn, c.wserr, s_over_b*100, s_sqrt_b, zn)
          print(cutflow_str, file=f)
      if do_json:
        # write JSON
        try:
          to_unicode = unicode
        except NameError:
          to_unicode = str
        with io.open(re.sub(".txt", ".json", outfile), 'w', encoding='utf8') as f_json:
            f_json.write(to_unicode(json.dumps({"tot_bkgd": tot_bkgd_dict, "bkgd": bkgd_list, "signal": sig_list}, indent=2, sort_keys=True,  separators=(',', ': '), ensure_ascii=False)))
      print(bottomrule, file=f)
      if do_latex:
        print(r"\end{tabular}", file=f)
        print(r"}", file=f)
        if ext_caption:
          print("\caption{{\\label{{ {:s} }} {:s} }}".format(label, caption), file=fcap)
        else:
          print("\caption{{\\label{{ {:s} }} {:s} }}".format(label, caption), file=f)
        print(r"\end{center}", file=f)
        if not ext_caption:
          print(r"\end{table}", file=f)
  except IOError:
      print ('Could not open file', outfile)

def save_cutflow_detailed(cuts, title='cutflow', outfile='detailed_cutflow.txt', caption='', label='', do_latex=False, ext_caption=False):

  if do_latex:
    toprule = r"\toprule"
    bottomrule = r"\bottomrule"
    midrule = r"\midrule"
  else:
    toprule = bottomrule = '*' * (190)
    midrule = '-' * (190)

  try:
    ensure_dir(outfile)
    if do_latex:
      f = open(re.sub(".txt", ".tex", outfile), 'w')
      if ext_caption:
        fcap = open(re.sub(".txt", "_caption.tex", outfile), 'w')
    else:
      f = open(outfile, 'w')

    if do_latex:
      if not ext_caption:
        print(r"\begin{table}[!ht]", file=f)
      print(r"\tiny", file=f)
      print(r"\begin{center}\renewcommand\arraystretch{1.6}", file=f)
      print(r"\sisetup{round-mode=figures, round-precision=2, group-digits = true, separate-uncertainty=true}", file=f)
      print(r"\scalebox{0.4}{", file=f)
      print(r"\begin{tabular}{l | ", file=f)
      print(r"S[round-mode=places]|", file=f)
      print(r"S[scientific-notation = true]|", file=f)
      print(r"S[scientific-notation = true]|", file=f)
      print(r"S|", file=f)
      print(r"S", file=f)
      print(r"}", file=f)
    print(toprule, file=f)
    if do_latex:
      print("\multicolumn{{6}}{{c}}{{ {} }} \\\\[0.2cm]".format(title), file=f)
    else:
      print(title, file=f)
    print(toprule, file=f)
    if do_latex:
      # print(r"Cut & {$N^{\mathrm{raw}}$} & {$N^{\mathrm{w}}$} & {$N$} & {$\eff$ [\%]} & {$\releff$ [\%]} \\", file=f)
      print(r"Cut & {$N^{\mathrm{raw}}$} & {$\eff$ [\%]} & {$\releff$ [\%]} & {$N^{\mathrm{w}}$} & {$N$} \\", file=f)
    else:
      print("{: <25} | {: <21} | {: <21} | {: <21} | {: <8} | {: <8}".format(
        "Cut", "nraw", "nweighted", "n", "eff", "effrel"), file=f)
    print(midrule, file=f)

    eff = releff = 100.
    n_prev = -1
    #wsn_prev = -1
    for i, (_, _, tag, c) in enumerate(cuts):
      if (i==0):
        n_initial = c.n
      if (i!=0):
        if (n_initial>0): eff = c.n/n_initial*100.
        else: eff = 0
        if (n_prev>0): releff = c.n/n_prev*100.
        else: releff = 0
      n_prev = c.n
      # if (i==0):
      #   wsn_initial = c.wsn
      # if (i!=0):
      #   if (wsn_initial>0): eff = c.wsn/wsn_initial*100.
      #   else: eff = 0
      #   if (wsn_prev>0): releff = c.wsn/wsn_prev*100.
      #   else: releff = 0
      # wsn_prev = c.wsn
      if do_latex:
          # cutflow_str = "{} & \\num{{{:.1f}}} & \\num{{{:.1uS}}} & \\num{{{:.1uS}}} & \\num{{{:g}}} & \\num{{{:g}}} \\\\".format(
          # tag, ufloat(c.n, c.err), ufloat(c.wn, c.werr), ufloat(c.wsn, c.wserr), eff, releff)
          cutflow_str = "{} & \\num{{{:.1f}}} & \\num{{{:g}}} & \\num{{{:g}}} & \\num{{{:.1uS}}} & \\num{{{:.1uS}}} \\\\".format(
          tag, ufloat(c.n, c.err), eff, releff, ufloat(c.wn, c.werr), ufloat(c.wsn, c.wserr))

          cutflow_str = cutflow_str.replace(r'+/-', r'\pm')
          cutflow_str = re.sub('num{[0\.]*0\\\\pm0}', 'num{0.0\pm0.0}', cutflow_str)
      else:
        cutflow_str = "{: <25} | {:.2e} +/- {:.2e} | {:.2e} +/- {:.2e} | {:.2e} +/- {:.2e} | {:.2e} | {:.2e}".format(
          cut, c.n, c.err, c.wn, c.werr, c.wsn, c.wserr, eff, releff)
      print(cutflow_str, file=f)
    print(bottomrule, file=f)
    if do_latex:
      print(r"\end{tabular}", file=f)
      print(r"}", file=f)
      if ext_caption:
        print("\caption{{\\label{{ {:s} }} {:s} }}".format(label, caption), file=fcap)
      else:
        print("\caption{{\\label{{ {:s} }} {:s} }}".format(label, caption), file=f)
      print(r"\end{center}", file=f)
      if not ext_caption:
        print(r"\end{table}", file=f)

  except IOError:
      print ('Could not open file', outfile)

def save_cutflow_detailed_signal(cuts, title='signal cutflow', outfile='detailed_cutflow_signal.txt', caption = '', label = '', do_latex=False, ext_caption=False):

  if do_latex:
    toprule = r"\toprule"
    bottomrule = r"\bottomrule"
    midrule = r"\midrule"
  else:
    toprule = bottomrule = '*' * (190)
    midrule = '-' * (190)

  try:
    ensure_dir(outfile)
    if do_latex:
      f = open(re.sub(".txt", ".tex", outfile), 'w')
      if ext_caption:
        fcap = open(re.sub(".txt", "_caption.tex", outfile), 'w')
    else:
      f = open(outfile, 'w')

    if do_latex:
      if not ext_caption:
        print(r"\begin{table}[!ht]", file=f)
      print(r"\tiny", file=f)
      print(r"\begin{center}\renewcommand\arraystretch{1.6}", file=f)
      print(r"\sisetup{round-mode=figures, round-precision=2, group-digits = true, separate-uncertainty=true}", file=f)
      print(r"\scalebox{0.4}{", file=f)
      print(r"\begin{tabular}{l | ", file=f)
      print(r"S[round-mode=places]|", file=f)
      print(r"S[scientific-notation = true]|", file=f)
      print(r"S|", file=f)
      print(r"S|", file=f)
      print(r"S[round-mode=places]|", file=f)
      print(r"S[scientific-notation = true]|", file=f)
      print(r"S|", file=f)
      print(r"S|", file=f)
      print(r"S|", file=f)
      print(r"S", file=f)
      print(r"}", file=f)
    print(toprule, file=f)
    if do_latex:
      print("\multicolumn{{11}}{{c}}{{ {} }} \\\\[0.2cm]".format(title), file=f)
    else:
      print(title, file=f)
    print(toprule, file=f)
    if do_latex:
      print(r"Cut & {$N_S^{\mathrm{raw}}$} & {$N_S$} & {$\eff_S$ [\%]} & {$\releff_S$ [\%]} & {$N_{B}^{\mathrm{raw}}$} & {$N_B$} & {$\eff_B$ [\%]} & {$\releff_B$ [\%]} & {$N_S/\sqrt{N_B}$} & {$\Zn$} \\", file=f)
    else:
      print("{: <25} | {: <21} | {: <21} | {: <8} | {: <8} | {: <21} | {: <21} | {: <8} | {: <8} | {: <8} | {: <8}".format(
        "Cut", "nSraw", "nS", "effS", "effSrel", "nBraw", "nB", "effB", "effBrel", "SsqrtB", "Zn"), file=f)
    print(midrule, file=f)

    seff = sreleff = beff = breleff = 100.
    s_wsn_prev = -1
    b_wsn_prev = -1
    for i, (_, _, tag, s, b) in enumerate(cuts):
      if (i==0):
        s_wsn_initial = s.wsn
        b_wsn_initial = b.wsn
      if (i!=0):
        if (s_wsn_initial>0): seff = s.wsn/s_wsn_initial*100.
        else: seff = 0
        if (b_wsn_initial>0): beff = b.wsn/b_wsn_initial*100.
        else: beff = 0
        if (s_wsn_prev>0): sreleff = s.wsn/s_wsn_prev*100.
        else: sreleff = 0
        if (b_wsn_prev>0): breleff = b.wsn/b_wsn_prev*100.
        else: breleff = 0
      s_wsn_prev = s.wsn
      b_wsn_prev = b.wsn
      sq = s.wsn/np.sqrt(b.wsn)
      zn = ROOT.RooStats.NumberCountingUtils.BinomialExpZ(s.wsn, b.wsn, 0.3)
      if (zn <0): zn = 0
      if (zn == float('Inf')): zn = 0
      if do_latex:
          # Signal
          cutflow_str = "{} & \\num{{{:.1f}}} & \\num{{{:.1uS}}} & \\num{{{:g}}} & \\num{{{:g}}}".format(
          tag, ufloat(s.n, s.err), ufloat(s.wsn, s.wserr), seff, sreleff)
          # Background
          cutflow_str += " & \\num{{{:.1f}}} & \\num{{{:.1uS}}} & \\num{{{:g}}} & \\num{{{:g}}} & \\num{{{:g}}} & \\num{{{:g}}}\\\\".format(
          ufloat(b.n, b.err), ufloat(b.wsn, b.wserr), beff, breleff, sq, zn)

          cutflow_str = cutflow_str.replace(r'+/-', r'\pm')
          cutflow_str = re.sub('num{[0\.]*0\\\\pm0}', 'num{0.0\pm0.0}', cutflow_str)
      else:
        cutflow_str = "{: <25} | {:.2e} +/- {:.2e} | {:.2e} +/- {:.2e} | {:.2e} | {:.2e}".format(
          cut, s.n, s.err, s.wsn, s.wserr, seff, sreleff)
        cutflow_str += " | {:.2e} +/- {:.2e} | {:.2e} +/- {:.2e} | {:.2e} | {:.2e} | {:8.2f} | {:8.2f}".format(
          b.n, b.err, b.wsn, b.wserr, beff, breleff, sq, zn)
      print(cutflow_str, file=f)
    print(bottomrule, file=f)
    if do_latex:
      print(r"\end{tabular}", file=f)
      print(r"}", file=f)
      if ext_caption:
        print("\caption{{\\label{{ {:s} }} {:s} }}".format(label, caption), file=fcap)
      else:
        print("\caption{{\\label{{ {:s} }} {:s} }}".format(label, caption), file=f)
      print(r"\end{center}", file=f)
      if not ext_caption:
        print(r"\end{table}", file=f)

  except IOError:
      print ('Could not open file', outfile)


if __name__ == "__main__":
  class CustomFormatter(argparse.ArgumentDefaultsHelpFormatter):
    pass

  __version__ = subprocess.check_output(["git", "describe", "--always"], cwd=os.path.dirname(os.path.realpath(__file__))).strip()
  __short_hash__ = subprocess.check_output(["git", "rev-parse", "--short", "HEAD"], cwd=os.path.dirname(os.path.realpath(__file__))).strip()

  parser = argparse.ArgumentParser(description='Author: Giordon Stark. v.{0}'.format(__version__),
                                   formatter_class=lambda prog: CustomFormatter(prog, max_help_position=30))

  parser.add_argument('-v','--verbose', dest='verbose', action='count', default=0, help='Enable verbose output of various levels. Use --debug to enable output for debugging.')
  parser.add_argument('--debug', dest='debug', action='store_true', help='Enable ROOT output and full-on debugging. Use this if you need to debug the application.')
  parser.add_argument('-b', '--batch', dest='batch_mode', action='store_true', help='Enable batch mode for ROOT.')
  parser.add_argument('-l', '--latex', dest='do_latex', action='store_true', help='Save latex tables.')
  parser.add_argument('--external-caption', dest='ext_caption', action='store_true', help='Captions in separate file. Also, skip table environment around tabulars (requires \'--latex\').')
  parser.add_argument('--json', dest='do_json', action='store_true', help='Save JSON tables.', default=False)
  parser.add_argument('--config', required=True, type=str, dest='config_file', metavar='<file.yml>', help='YAML file specifying input files and asssociated names.')
  parser.add_argument('--weights', required=True, type=str, dest='weights_file', metavar='<file.json>', help='json file specifying the weights by dataset id.')
  parser.add_argument('--lumi', required=False, type=float, dest='global_luminosity', metavar='<ifb>', help='luminosity to use for scaling.')
  parser.add_argument('--type', type=str, dest='cutflow_type', choices = ['summary', 'detailed', 'detailed-signal'], help="Specify type of cutflow to make.", default='summary')
  parser.add_argument('-i', '--input', dest='top_level', type=str, help='Top level directory containing plots.', default='all')
  parser.add_argument('--top-dir', action='store_true', help='If plots are in the top directory')

  # parse the arguments, throw errors if missing any
  args = parser.parse_args()

  try:
    # start execution of actual program
    import timing

    # set verbosity for python printing
    if args.verbose < 5:
      logger.setLevel(25 - args.verbose*5)
    else:
      logger.setLevel(logging.NOTSET + 1)

    with tempfile.NamedTemporaryFile() as tmpFile:
      if not args.debug:
        ROOT.gSystem.RedirectOutput(tmpFile.name, "w")

      # if flag is shown, set batch_mode to true, else false
      ROOT.gROOT.SetBatch(args.batch_mode)

      configs = yaml.load(file(args.config_file))
      # get the samples configuration
      groups = dict([(group['name'], group) for group in configs['groups']])
      # get the cutflows configuration
      cutflows = configs.get('cutflows')
      # global configurations for cutflows
      cutflows_config = cutflows.get('config', {})
      # get the cutflows paths
      cutflows_paths = cutflows.get('paths')

      # get the weights configurations for scaling
      weights = json.load(file(args.weights_file))

      # add and group histograms
      hall = ph.HChain(args.top_level)
      if args.top_dir:
        hall = ph.HChain(None)
      for group in configs['groups']:
        hc = ph.HGroup(group['name'])
        try:
          logger.log(25, "Group: {0:s}, type: {0:s}".format(group['name'], group['type']))
        except KeyError:
          logger.log(25, "Group: {0:s}".format(group['name']))
        for f in group['files']:
          logger.log(25, "\tPattern: {0:s}".format(f))
          for fname in glob.glob(f):
            logger.log(25, "\t\tAdding {0:s}".format(fname))
            rootFile = root_open(fname)
            hc.append(rootFile)
        if len(hc) == 0:
          raise ValueError("{0:s} has no files loaded.".format(group['name']))
        logger.log(25, "\tAdding {0:s}".format(hc))
        hall.append(hc)

      # store the cuts (using the cutflows: paths: label as 'key')
      all_cuts = dict()
      for path in cutflows_paths.keys():

        h = reduce(lambda x,y: getattr(x, y, None), (item for item in path.split('/') if item != args.top_level), hall)
        hists = map(lambda hgroup: hgroup.flatten, h)

        for hgroup in h:
          # one cut object per group
          cut = Cut()
          for hist in hgroup:
            # look up weights by did
            did = get_did(hist)
            weight = weights.get(did)
            if weight is None:
              raise KeyError("Could not find the weights for did=%s" % did)
            scale_factor = 1.0
            if weight.get('num events') == 0:
              raise ValueError("did=%s has num events == 0" % did)
            scale_factor /= weight.get('num events')
            scale_factor *= weight.get('cross section')
            scale_factor *= weight.get('filter efficiency')
            scale_factor *= weight.get('k-factor')
            scale_factor *= args.global_luminosity*1000
            scale_factor *= groups.get(hgroup.group).get('scale factor', 1.0)
            logger.info("Scale factor for {:s}: {:.6f}".format(did, scale_factor))

            # raw number of events
            n = hist.GetEntries()
            err = np.sqrt(n)

            # sum of event weights
            wn = hist.GetBinContent(1)
            werr = hist.GetBinError(1)
            # if n > 0:
            #   werr = err*float(wn)/float(n)
            # else:
            #   werr = 0

            # number of events with sample scale factors applied
            wsn = wn*scale_factor
            wserr = werr*scale_factor
            # add to cut
            cut.add(n, err, wn, werr, wsn, wserr)

          # Add cut to dictionary
          if path in all_cuts:
            tmp_dict = all_cuts[path]
            tmp_dict[hgroup.group] = cut
          else:
            all_cuts[path] = {hgroup.group : cut}

      # decide what type of cutflow to save
      if args.cutflow_type == 'summary':
        for path, cuts in all_cuts.iteritems():
          logger.log(25, "Saving summary cutflow for: {:s}".format(path))

          # import pdb; pdb.set_trace()
          # Separate signal and background
          cuts_signal = [(key, cuts[key]) for key in cuts if groups.get(key)['type'] == 'signal']
          cuts_background = [(key, cuts[key]) for key in cuts if groups.get(key)['type'] == 'background']

          # Sort signal cuts (assuming 'name' contains numbers corresponding to the mass points)
          cuts_signal = sorted(map((lambda (key, cut): ([float(i) for i in re.findall(r'[\d]+', key)], key, cut)), cuts_signal))
          # Sort background cuts (based on 'order' in config file)
          cuts_background = sorted(map((lambda (key, cut): (groups[key]['order'], key, cut)), cuts_background))

          outfile = cutflows_paths[path]['outfile']
          caption = cutflows_paths[path]['caption']
          label = cutflows_paths[path]['label']

          save_cutflow_summary(cuts_signal, cuts_background, outfile=outfile, caption=caption, label=label, do_latex=args.do_latex, ext_caption=args.ext_caption, do_json=args.do_json)

      elif args.cutflow_type == 'detailed':
        for sample in [s for s in groups]:
          logger.log(25, "Saving detailed cutflow for: {:s}".format(sample))

          # Loop over cutflow paths and create a list of cuts for this sample group
          cuts = []
          for path, cut_metadata in cutflows_paths.iteritems():
            # Get number of events for this group
            cut = all_cuts[path][sample]
            # (order, path/to/cutflow, label, signal_events, tot_bkgd_events)
            cuts.append((cut_metadata['order'], path, cut_metadata['label'], cut))

          # Sort cuts
          cuts = sorted(cuts)

          try:
            sample_name = groups[sample]['name']
          except KeyError:
            logger.error("'name' must be specified for each group of samples")
            exit(1)

          try:
            outfile = groups[sample]['outfile']
          except KeyError:
            outfile = './cutflow.txt'

          try:
            caption = groups[sample]['caption']
          except KeyError:
            caption = ''

          try:
            label = groups[sample]['label']
          except KeyError:
            label = ''

          save_cutflow_detailed(cuts, title=sample_name, outfile=outfile, caption=caption, label=label, do_latex=args.do_latex, ext_caption=args.ext_caption)

      elif args.cutflow_type == 'detailed-signal':
        # Loop over signal samples (save one histogram per signal sample
        for signal in [s for s in groups if groups[s]['type'] == 'signal']:
          logger.log(25, "Saving detailed signal cutflow for: {:s}".format(signal))

          # Loop over cutflow paths and create a list of cuts for this particular signal sample
          cuts = []
          for path, cut_metadata in cutflows_paths.iteritems():
            # Get number of signal events for this cut
            signal_cut = all_cuts[path][signal]
            # Get total number of background events for this cut
            tot_bkgd_cuts = Cut()
            for sample_name, group in groups.iteritems():
              if group['type'] == 'background':
                tot_bkgd_cuts.add_cut(all_cuts[path][sample_name])

            # (order, path/to/cutflow, label, signal_events, tot_bkgd_events)
            cuts.append((cut_metadata['order'], path, cut_metadata['label'], signal_cut, tot_bkgd_cuts))

          # Sort cuts
          cuts = sorted(cuts)

          try:
            signal_name = groups[signal]['name']
          except KeyError:
            logger.error("'name' must be specified for each group of samples")
            exit(1)

          try:
            outfile = groups[signal]['outfile']
          except KeyError:
            outfile = './cutflow.txt'

          try:
            caption = groups[signal]['caption']
          except KeyError:
            caption = ''

          try:
            label = groups[signal]['label']
          except KeyError:
            label = ''

          save_cutflow_detailed_signal(cuts, title=signal_name, outfile=outfile, caption=caption, label=label, do_latex=args.do_latex, ext_caption=args.ext_caption)

      if not args.debug:
        ROOT.gROOT.ProcessLine("gSystem->RedirectOutput(0);")

  except Exception, e:
    # stop redirecting if we crash as well
    if not args.debug:
      ROOT.gROOT.ProcessLine("gSystem->RedirectOutput(0);")

    logger.exception("{0}\nAn exception was caught!".format("-"*20))
