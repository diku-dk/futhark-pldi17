#!/usr/bin/env python

import numpy as np
import sys

import matplotlib

matplotlib.use('Agg') # For headless use

import matplotlib.pyplot as plt
import os

rodinia_programs = [("Backprop", "backprop"),
                    ("CFD", "cfd"),
                    ("HotSpot", "hotspot"),
                    ("K-means", "kmeans"),
                    ("LavaMD", "lavaMD"),
                    ("Myocyte", "myocyte"),
                    ("NN", "nn"),
                    ("Pathfinder", "pathfinder"),
                    ("SRAD", "srad")]

accelerate_programs = [("Crystal", "crystal"),
                       ("Fluid", "fluid"),
                       ("Mandelbrot", "mandelbrot"),
                       ("N-body", "nbody")]

finpar_programs = [("LocVolCalib", "LocVolCalib_large"),
                   ("OptionPricing", "OptionPricing_large")]

parboil_programs = [("MRI-Q", "mri-q")]

def ref_filename_closure(ref):
    return lambda d, filename: os.path.join(d, filename + '-' + ref + '.avgtime')

def fut_filename(d, filename):
    return os.path.join(d, filename + '-futhark.avgtime')

def get_ref_avgtime(d, ref_filename, filename):
    with open(ref_filename(d, filename)) as f:
        return '%.1f' % float(f.read())

def get_fut_avgtime(d, ref_filename, filename):
    with open(fut_filename(d, filename)) as f:
        return '%.1f' % float(f.read())

def get_avgtimes(d, ref_filename, filename):
    return (get_ref_avgtime(d, ref_filename, filename),
            get_fut_avgtime(d, ref_filename, filename))


def table_info_closure(ref_filename):
    def table_info(x):
        name, filename = x
        try:
            (ref_avgtime, fut_avgtime) = get_avgtimes('runtimes', ref_filename, filename)
            try:
                aux_fut_avgtime = get_fut_avgtime('aux_runtimes', ref_filename, filename)
                try:
                    aux_ref_avgtime = get_ref_avgtime('aux_runtimes', ref_filename, filename)
                    return (name, ref_avgtime, fut_avgtime, aux_ref_avgtime, aux_fut_avgtime)
                except:
                    return (name, ref_avgtime, fut_avgtime, '---', aux_fut_avgtime)
            except:
                return (name, ref_avgtime, fut_avgtime, '---', '---')
        except:
            sys.stderr.write('Skipping %s as the file could not be opened.\n' % name)
            return None
    return table_info

to_table = list(filter(lambda x: x is not None,
                       map(table_info_closure(ref_filename_closure('rodinia')), rodinia_programs) +
                       map(table_info_closure(ref_filename_closure('finpar')), finpar_programs) +
                       map(table_info_closure(ref_filename_closure('parboil')), parboil_programs) +
                       map(table_info_closure(ref_filename_closure('accelerate')), accelerate_programs)))

print(r'''\begin{tabular}{lrrrr}''')

if os.getenv('FUTHARK_LEGENDS'):
    print(r'''& \multicolumn{2}{c}{\textbf{NVIDIA GTX780}} & \multicolumn{2}{c}{\textbf{AMD W8100}} \\''')

print(r'''\textbf{Benchmark} & \textbf{Ref.} & \textbf{Futhark} & \textbf{Ref.} & \textbf{Futhark}\\''')

for row in to_table:
    print(r'''%s & %s & %s & %s & %s \\''' % row)

print(r'''\end{tabular}''')
