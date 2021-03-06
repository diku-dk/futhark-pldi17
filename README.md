Experimentation Infrastructure for PLDI 2017 Paper
==

This bundle contains scripts and benchmarks for reproducing the
empirical evaluation of the paper *Futhark: Purely Functional
GPU-programming with Nested Parallelism and In-place Array Updates*,
to appear at PLDI 2017.  The primary research artifact of our work is
the Futhark compiler itself, which is [freely
available](https://github.com/HIPERFIT/futhark) and has [its own
documentation](https://futhark.readthedocs.io/en/latest/).  This
bundle contains infrastructure, hacks, and tools for orchestrating the
execution of Futhark implementations of various benchmarks, as well as
running the original reference implementations.  Tools are provided
for computing and visualising relative speedups.  The repository does
not itself contain the Futhark compiler or any benchmark
implementations.  Some of these will be downloaded automatically, but
others must be installed manually (as described below).  The intent is
to make it clear how we modify the reference implementations.  In
practice, we only modify Rodinia, via the file
`rodinia_3.1-some-instrumentation.patch`.

This infrastructure depends not only on the Futhark compiler itself,
but also on four third-party benchmark suites (Rodinia, Parboil,
FinPar, and Accelerate), the GPU setup on the host system, and some
Python libraries for automatic plot generation.  To manage this, we
have put effort into documenting the dependencies and creating
workarounds for disabling parts of the infrastructure.  Even if you
are unable to install all of the reference benchmarks, you should
still be able to get partial results.  The Rodinia and FinPar
benchmark suites are generally the easiest to run, as they are
downloaded automatically by our scripts.

Please read this document carefully or you are likely to have a bad
time.  This infrastructure has been tested only on Linux, and some
Unix knowhow is likely necessary to follow these instructions.  The
system must have a GPU, and a working OpenCL setup (see specific
requirements below).

The main interface to the infrastructure is `make`.  The makefile
contains various targets for running sub-parts of the infrastructure,
so even if not everything works (or you don't want to bother with
installing the more complicated parts), you can still get partial
results.  The valid targets are listed at the end of this guide.  If
an intermediate step fails due to missing dependencies or
misconfiguration, you must run `make clean` before proceeding, as it
is likely that corrupted files will be left behind.

Running all benchmarks should take less than an hour, depending on the
speed of your system.

System Requirements
-------------------

Every program mentioned below must be available in `PATH`.  You can
modify the `PATH` (and other environment variables) before running
`make`.

 * A Unix system with basic tools: `patch`, `md5sum`.

 * `python3` with a working Matplotlib and Numpy, used for plotting
    and generating input data.  **For Parboil to work, it is important
    that plain `python` is a Python 2.**

 * Some Accelerate examples: `accelerate-nbody`,
   `accelerate-crystal`, `accelerate-mandelbrot`, `accelerate-fluid`.

 * `futhark-opencl`.

The system must be able to compile OpenCL and CUDA programs with `gcc`
without requiring any special compiler directives or include paths.
That is, `gcc opencl_test.c -lOpenCL` and `nvcc cuda_test.cu` must
work.  You can run `make sanity_check_opencl` and `make
sanity_check_cuda` to quickly check whether your system is capable of
this.  You may have to modify the environment variables `CPATH`,
`LIBRARY_PATH`, and `LD_LIBRARY_PATH` to point to the appropriate
locations locations.  For example, on NVIDIA systems, the following is
often necessary:

    export PATH=/usr/local/cuda/bin:$PATH
    export CPATH=/usr/local/cuda/include:$CPATH
    export LIBRARY_PATH=/usr/local/cuda/lib64:$LIBRARY_PATH
    export LD_LIBRARY_PATH=/usr/local/cuda/lib64/:$LD_LIBRARY_PATH

Reference implementations using CUDA will only work if the system has
an NVIDIA GPU.  For implementations using OpenCL (including all
Futhark implementations), any AMD or NVIDIA GPU made within the last
five years and with at least 3GiB of memory should work.  They may
also work on recent Intel GPUs, although you may run out of memory.

OpenCL/CUDA Device Selection
----------------------------

All Futhark implementations, and most of the reference
implementations, interact with the GPU through the OpenCL library,
which must be installed and working.  A few (in particular Accelerate)
use NVIDIAs CUDA.  For OpenCL, most benchmarks will pick the first
OpenCL platform and device found.  Some will explicitly only look for
devices that register themselves as GPUs; whereas others (including
Futhark) are less picky, and will happily run on an OpenCL CPU device.
It is advisable to ensure that only one platform and/or device can be
found by the benchmarks.  On Linux, OpenCL works by looking for
platform files in the directory `/etc/OpenCL/vendors` - you can
temporarily remove the ones that you do not want to use.  Getting this
right is likely to involve hackery and manual labour, as configuring
GPUs on Linux remains one of the great unsolved problems in computer
science.  We recommend the use of [clinfo][] for inspecting the state
of the OpenCL setup.

[clinfo]: https://github.com/Oblomov/clinfo

Futhark requirements
--------------------

The Futhark compiler has its own [installation instructions][],
including both nightly binary releases (for Linux) and instructions on
compiling from source.  In short, to do the latter, install [The
Haskell Tool Stack][], go to a checkout of the [futhark repository][],
and run `stack setup` followed by `stack install`.  The Futhark
compiler binaries will be in `$HOME/.local/bin`, which must be added
to the `PATH`.

At the time this document was written, the newest Futhark compiler Git
revision was `78c956ba58057ca6773cefb466efef2fa65c1386`.

[installation instructions]: https://futhark.readthedocs.io/en/latest/installation.html
[The Haskell Tool Stack]: https://docs.haskellstack.org/en/stable/README/
[futhark repository]: https://github.com/HIPERFIT/futhark

Futhark benchmarks
------------------

The [futhark-benchmarks][] repository will be automatically downloaded
by the makefile, but note that it always downloads the *newest*
version of the repository.  This is to ensure that it retrieves a
version that works with the newest version of the Futhark compiler.

At the time this document was written, the newest Futhark benchmarks
revision was `c3eee750b3c6aece2d52d2417537d093a9ee8148`.

[futhark-benchmarks]: https://github.com/HIPERFIT/futhark-benchmarks

Rodinia requirements
--------------------

The makefile automatically downloads the appropriate version of
[Rodinia][] and patches the relevant benchmarks with instrumentation
code and other necessary fixes.

[Rodinia]: http://lava.cs.virginia.edu/Rodinia/download_links.htm

Parboil requirements
--------------------

[Parboil][] requires a click-through license and so cannot be
automatically downloaded by the makefile.  Futhermore, Parboil must
often be manually configured with respect to include paths.  The
makefile assumes that the environment variable `PARBOIL_LOCATION`
points to a working Parboil setup (defaults to `$HOME/parboil` if the
variable is not set).  This infrastructure has been tested with
Parboil 2.5.  You can run `make sanity_check_parboil` to check whether
your Parboil setup works.

[Parboil]: http://impact.crhc.illinois.edu/parboil/parboil.aspx

Accelerate requirements
-----------------------

Our Accelerate benchmarks come from [accelerate-examples][].
Accelerate has its own installation instructions.  If you follow
these, the necessary binaries will be in `$HOME/.local/bin`, which
must be added to the `PATH`.

[accelerate-examples]: https://github.com/AccelerateHS/accelerate-examples/

FinPar requirements
-------------------

Like Rodinia, [FinPar][] is automatically downloaded.

[FinPar]: https://github.com/HIPERFIT/finpar

Usage
-----

Once everything is installed and working, a simple `make` will run
every benchmark and put runtimes and Futhark speedups in the
`runtimes` directory.  The screen will be littered with messages, but
all the important output will be stored in the `runtimes` directory.

There are several other makefile targets available:

  `make benchmark_easiest`: Run all benchmarks that require only
  OpenCL (no CUDA), and which can be installed automatically by the
  makefile.  **This target is the one most likely to Just Work**, and
  you can `make speedup.pdf` afterwards to get at least a partial
  visualisation.  You will still need to manually install the Futhark
  compiler, and ensure that `make sanity_check_opencl` works.

  `make benchmark_rodinia`: Run just the benchmarks from Rodinia and
  put the results in `runtimes/`.

  `make benchmark_accelerate`: Run just the benchmarks from Accelerate
  and put the results in `runtimes/`.

  `make benchmark_finpar`: Run the benchmarks from FinPar and put the results in `runtimes/`.

  `make benchmark_parboil`: Run the benchmarks from Parboil and put the results in `runtimes/`.

  `make benchmark`: Run all benchmarks.

  `make benchmark_futhark`: Run all Futhark implementation and produce
  `.runtimes` and `.avgtime` files in the `runtimes/` directory.  Does
  not run reference implementations, and thus does not produce
  `.speedup` files.

  `make speedup.pdf`: Generate a graph of all computed speedups.
  Runtime information from both `runtimes/` and `aux_runtimes/` is
  used (the latter is optional).  You will have to create the latter
  directory yourself, preferably by copying it from the `runtimes/`
  directory of some other machine.

  `make runtimes.tex`: Generate a table of all runtimes and speedups.
  As with `make speedup.pdf`, also looks for an `aux_runtimes/`
  directory.

  `make runtimes/*foo*.speedup`: Run one specific named benchmark and
  compute its speedup.  *foo* can be one of `srad`, `hotspot`, `nn`,
  `backprop`, `cfd`, `kmeans`, `lavaMD`, `pathfinder`, `myocyte`,
  `fluid`, `mandelbrot`, `nbody`, `crystal`, `LocVolCalib_large`,
  `OptionPricing_large`, `mri-q`.

  `make benchmark_opencl`: Run all the benchmarks that require only
  OpenCL.  This is the target you want if you are running on a
  non-NVIDIA system.

  `make sanity_check_cuda`: Check whether simple OpenCL programs can
  be compiled and run.

  `make sanity_check_opencl`: Check whether simple CUDA programs can
  be compiled and run.

  `make sanity_check_parboil`: Check whether Parboil is available and
  working.

  `make benchmark_noinplace_kmeans`: Run a variant of the kmeans
  benchmark that does not use in-place updates and print the resulting
  runtime to the screen.

  `make benchmark_noinplace_LocVolCalib`: Run a variant of the
  LocVolCAlib benchmark that does not use in-place updates and print
  the resulting runtime to the screen.

Paper Data
----------

Runtime data used to compute the figures in the paper can be found in
the `paper_data` directory.
