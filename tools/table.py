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

def get_avgtimes(d, ref_filename, filename):
    with open(ref_filename(d, filename)) as ref_f:
        with open(fut_filename(d, filename)) as fut_f:
            return ('%.1f' % float(ref_f.read()),
                    '%.1f' % float(fut_f.read()))


def table_info_closure(ref_filename):
    def table_info(x):
        name, filename = x
        (ref_avgtime, fut_avgtime) = get_avgtimes('runtimes', ref_filename, filename)
        try:
            (aux_ref_avgtime, aux_fut_avgtime) = get_avgtimes('aux_runtimes', ref_filename, filename)
            return (name, ref_avgtime, fut_avgtime, aux_ref_avgtime, aux_fut_avgtime)
        except:
            return (name, ref_avgtime, fut_avgtime, '---', '---')
    return table_info

to_table = list(map(table_info_closure(ref_filename_closure('rodinia')), rodinia_programs) +
                map(table_info_closure(ref_filename_closure('finpar')), finpar_programs) +
                map(table_info_closure(ref_filename_closure('parboil')), parboil_programs) +
                map(table_info_closure(ref_filename_closure('accelerate')), accelerate_programs))

print(r'''
\begin{tabular}{lrrrr}
& \multicolumn{2}{c}{\textbf{NVIDIA GTX780}} & \multicolumn{2}{c}{\textbf{AMD W8100}} \\
\textbf{Benchmark} & \textbf{Ref.} & \textbf{Futhark} & \textbf{Ref.} & \textbf{Futhark}\\
''')

for row in to_table:
    print(r'''%s & %s & %s & %s & %s \\''' % row)

print(r'''\end{tabular}''')
