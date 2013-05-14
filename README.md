bench-crypto-seed
=================

Benchmark of various implementation of the Korean SEED block cipher algorithm
- botan
- libgcrypt
- crypto++

Usage:
./host-prepare.sh will (supposedly) install the needed libraries on the system

./run-bench.sh will run some benchmarks and report some results in a table:
- please have the following cmdline tools installed:
	time, valgrind, strace, perf
 ( I didn't want to make a script to build them from sources as well)
- you may tweak the parameters in the run-bench.sh script if you want a different range of values
- tests measure this:
	0 - application running time
	1 - heap usage in bytes
	2 - no. of write syscalls
	3 - no. of instructions in program
