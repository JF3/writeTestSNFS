all: test check 

test: test.cpp
	mpiicpc test.cpp -o test

check: check.cpp
	icpc check.cpp -o check
