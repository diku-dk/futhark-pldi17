RODINIA_URL=http://www.cs.virginia.edu/~kw5na/lava/Rodinia/Packages/Current/rodinia_3.1.tar.bz2
RODINIA_MD5=047d983e62107972f217921aa0027b05  rodinia_3.1.tar.bz2
RUNS=10

BENCHMARKS=srad

all: $(BENCHMARKS:%=runtimes/%-rodinia.avgtime) $(BENCHMARKS:%=runtimes/%-futhark.avgtime)

runtimes/%.avgtime: runtimes/%.runtimes
	awk '{sum += strtonum($$0) / 1000.0} END{print sum/NR}' < $< > $@

runtimes/srad-rodinia.runtimes: rodinia_3.1-patched
	mkdir -p runtimes
	(cd $</opencl/srad && make && RODINIA_RUNS=$(RUNS) ./run)
	cp $</opencl/srad/runtimes $@

runtimes/srad-futhark.runtimes: futhark-benchmarks
	mkdir -p runtimes
	futhark-opencl $</rodinia/srad/srad_core.fut
	$</rodinia/srad/srad_core -r $(RUNS) -t $@ < $</rodinia/srad/data/image.in > /dev/null

futhark-benchmarks:
	git clone --depth 1 https://github.com/HIPERFIT/futhark-benchmarks.git

rodinia_3.1-patched: rodinia_3.1
#	cp -r rodinia_3.1 rodinia_3.1-patched
#	patch -p0 < rodinia_3.1-some-instrumentation.patch

rodinia_3.1: rodinia_3.1.tar.bz2
	@if ! md5sum --quiet -c rodinia_3.1.tar.bz2.md5; then \
          echo "Your rodinia_3.1.tar.bz2 has the wrong MD5-sum - delete it and try again."; exit 1; fi
	tar jxf rodinia_3.1.tar.bz2

rodinia_3.1.tar.bz2:
	wget http://www.cs.virginia.edu/~kw5na/lava/Rodinia/Packages/Current/rodinia_3.1.tar.bz2

clean:
	rm -rf rodinia_3.1
	rm -f rodinia_3.1.tar.bz2
