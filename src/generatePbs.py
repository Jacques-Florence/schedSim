#!/usr/bin/env python

import os
import sys

i = sys.argv[1]

filename = "job" + str(i) + ".pbs"
	
with open(filename, "w") as file:
	file.write("#PBS N job" + str(i) + "\n")
	file.write("#PBS -l nodes=1:ppn=2\n")
	file.write("#PBS -l mem=2gb\n")
	file.write("#PBS -l walltime=20:00:00\n")
	file.write("#PBS -q eceforce-6\n")
	file.write("#PBS -j oe\n")
	file.write("#PBS -o scratch/job" + str(i) + ".out\n")
	file.write("#PBS -m abe\n")
	file.write("#PBS -M jacques.florence@gatech.edu\n")
	file.write("module load gcc/4.9.0\n")
	file.write("module load python/2.7\n")
	file.write("time ./run.sh -configNumber " + str(i) + "\n")






