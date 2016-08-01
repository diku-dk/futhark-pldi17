#!/usr/bin/env python

import numpy as np
import sys

import matplotlib

matplotlib.use('Agg') # For headless use

import matplotlib.pyplot as plt
import os

outputfile = sys.argv[1]

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

def plotting_info(x):
    name, filename = x
    with open(os.path.join('runtimes', filename + '.speedup')) as f:
        return (name, float(f.read()))

to_plot = map(plotting_info, rodinia_programs + accelerate_programs + finpar_programs)

program_names = [ name for (name, _) in to_plot ]
program_speedups = [ speedup for (_, speedup) in to_plot ]

N = len(to_plot)

# the width of the bars
width = 0.5
# the x locations for the bars
ind = np.arange(N)+width

fig, ax = plt.subplots()

font = {'family': 'normal',
        'size' : 10}
plt.rc('font', **font)
grey='#aaaaaa'

ax.set_ylim([0.0,6.0])
ax.set_xlim([0.0,ind[-1]+width*2])
ax.set_ylabel('Speedup')
ax.set_xticks(ind+width/2)
ax.set_xticklabels(program_names)
ax.xaxis.set_ticks_position('none')
ax.yaxis.set_ticks_position('none')
ax.yaxis.grid(color=grey,zorder=0)
ax.spines['bottom'].set_color(grey)
ax.spines['top'].set_color('none')
ax.spines['left'].set_color(grey)
ax.spines['right'].set_color('none')

gridlines = ax.get_xgridlines() + ax.get_ygridlines()
for line in gridlines:
    line.set_linestyle('-')

stagger = 0
for t in ax.get_xticklabels( ):
    t.set_y( stagger )
    if stagger == 0:
        stagger = -0.13
    else:
        stagger = 0

rects = ax.bar(ind, program_speedups, width, color='#0033cc', zorder=3)

def label_rect(rect):
    height = min(6.0, rect.get_height())
    ax.text(rect.get_x() + rect.get_width()/2., 1.05*height+0.1,
            '%.2f' % height,
            ha='center', va='bottom')

map(label_rect, rects)

fig.set_size_inches(8.5, 1.5)
plt.rc('text', usetex=True)
plt.savefig(outputfile, bbox_inches='tight')
