#! /usr/bin/python

import os
import re
import sys

with open("data/sorted") as f:
	counter = 1;
	for line in f:
		if not line.startswith("configuration"):
			continue;
		while not re.match(r"^configuration0*" + str(counter), line):
			print counter
			counter += 1
		counter += 1
