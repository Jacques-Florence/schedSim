#!/usr/bin/env python
import matplotlib
import matplotlib.pyplot as plt
import sys

filename1 = "rmsTempProfile"
filename2 = "rlTempProfile"


with open(filename1) as f:
	time1 = []
	temp1 = []
	for line in f:
		entry = line.split(":")
		time1.append(float(entry[0]))
		temp1.append(float(entry[1]))
with open(filename2) as f:
	time2 = []
	temp2 = []
	for line in f:
		entry = line.split(":")
		time2.append(float(entry[0]))
		temp2.append(float(entry[1]))

matplotlib.rcParams.update({'font.size': 22})
plt.plot(time1, temp1, 'r', linewidth=3, linestyle='dashed', label="rate-monotonic scheduling")
plt.plot(time2, temp2, 'b', linewidth=2, label="reinforcement learning")
plt.legend(loc='lower right')
plt.xlabel("time")
plt.ylabel("temperature (Celsius)")
plt.show()
