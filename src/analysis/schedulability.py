#!/usr/bin/env python

import os
import re
import sys

def schedulability():
	configFilename = ""
	if (len(sys.argv) < 2):
		configFilename = "configuration.conf"
	else:
		configFilename = sys.argv[1]

	configPath = "configuration/" + configFilename

	#let's get the running time:
	with open(configPath) as f:
		for line in f:
			entrymatch = re.match(r'^runningTime *= *([0-9]+)', line) #TODO we should also check that we are in section [scheduler]...
			if entrymatch:
				runningTime = float(entrymatch.group(1))
			
	reportsFolder = "scratch"

	missFilename = reportsFolder + "/" + configFilename + "deadlineMissesReport.txt"

	with open(missFilename) as f:
		f.readline() #discard first line
		entries = [[float(elem) for elem in line.split(":")] for line in f]
		if len(entries) == 0:
			return 1
		else:
			if entries[len(entries)-1][0] < runningTime*0.9:
				return 1
			else:
				return 0


if __name__ == '__main__':
	schedulability()







