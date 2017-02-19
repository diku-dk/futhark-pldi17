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

parboil_programs = [("MRI-Q", "mri-q")]

def plotting_info(x):
    name, filename = x
    speedup_file = os.path.join('runtimes', filename + '.speedup')
    try:
        with open(speedup_file) as f:
            speedup = float(f.read())
            aux_speedup = 0.0
            try:
                with open(os.path.join('aux_runtimes', filename + '.speedup')) as f:
                    aux_speedup = float(f.read())
            except:
                aux_speedup = 0.0
            return (name, speedup, aux_speedup)
    except:
        print('Skipping %s as %s could not be opened' % (name,speedup_file))

to_plot = list(filter(lambda x: x is not None,
                      map(plotting_info,
                          rodinia_programs + finpar_programs + parboil_programs + accelerate_programs)))

program_names = [ name for (name, _, _) in to_plot ]
program_speedups = [ speedup for (_, speedup, _) in to_plot ]
program_aux_speedups = [ aux_speedup for (_, _, aux_speedup) in to_plot ]

N = len(to_plot)

# the widths of the bar
width = 0.5
def compute_space(x):
    if x[2] == 0.0:
        return width*2
    else:
        return width*3
spaces = np.array(list(map(compute_space, to_plot)))

# the x locations for the bars
ind = width+np.concatenate(([0], np.cumsum(spaces)[:-1]))

fig, ax = plt.subplots()

font = {'family': 'normal',
        'size' : 9}
plt.rc('font', **font)
grey='#aaaaaa'

ax.set_ylim([0.0,6.0])
ax.set_xlim([0.0,ind[-1]+1])
ax.set_ylabel('Speedup')
ax.set_xticks(ind+width)
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

rects = ax.bar(ind, program_speedups, width, color='#2255ee', zorder=3, edgecolor='white', label='GTX 780')
aux_rects = ax.bar(ind+width, program_aux_speedups, width, color='#ee5500', zorder=3, edgecolor='white', label='W8100')

def label_rect(rect):
    height = rect.get_height()

    if height == 0.0:
        return

    font = {'family': 'sans-serif',
            'weight': 'bold',
            'size': 8,
    }
    bounded_height = min(6.0, height)
    ax.text(rect.get_x() + rect.get_width(), 1.05*bounded_height,
            '%.2f' % height,
            ha='center', va='bottom', fontdict=font, rotation=45)

if os.getenv('FUTHARK_LEGENDS'):
    map(label_rect, rects)
    map(label_rect, aux_rects)
    ax.legend(bbox_to_anchor=(0., 1.15, 1., .115), loc=3, ncol=2, borderaxespad=0.)

fig.set_size_inches(8.5, 1.5)
plt.rc('text')
plt.savefig(outputfile, bbox_inches='tight')
