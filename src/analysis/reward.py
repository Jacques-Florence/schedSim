#!/usr/bin/env python
import matplotlib.pyplot as plt
import sys
import numpy
from math import floor

def movingAverage(x, N):
	cumsum = numpy.cumsum(numpy.insert(x, 0, 0))
	return (cumsum[N:] - cumsum[:-N])/N

filename = "reports/configuration.confrewardRecordReport.txt"
if (len(sys.argv) > 1):
	filename = sys.argv[1]

with open(filename) as f:
	print f.readline()
	time = []
	temp = []
	avg = []
	for line in f:
		entry = line.split(":")
		time.append(float(entry[0]))
		temp.append(float(entry[1]))

windowSize = 100
avg = [0] * (windowSize - 1)
avg = avg + list( movingAverage(temp, windowSize))

ratio = 0.999
avg  =  avg[int(floor(len(avg )*ratio)): len(avg )-1]
time = time[int(floor(len(time)*ratio)): len(time)-1]
temp = temp[int(floor(len(temp)*ratio)): len(temp)-1]




plt.plot(time, temp, 'r-')
plt.plot(time, avg, 'ro')
plt.show()
