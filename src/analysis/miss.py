#!/usr/bin/env python
import matplotlib.pyplot as plt
import sys
import itertools
def main():
	filename = "scratch/configuration.confdeadlineMissesReport.txt"
	if (len(sys.argv) > 1):
		filename = sys.argv[1]
	with open(filename) as f:
		print f.readline()
		entries = ((float(elem) for elem in line.split(":")) for line in f)
		(time, pid) = itertools.izip(*entries)

	missNumber(time);

	plt.suptitle(filename, fontsize=14, fontweight='bold')
	plt.plot(time, pid, 'ro')
	plt.axis([-1,max(time)+1,-1,max(pid) + 1])
	plt.show()


cutoffTime = 1800000;

def missNumber(time):
	if (len(time) == 0):
		print "No deadline misses";
		return;
	if (time[len(time)-1] <= cutoffTime):
		print "No deadline misses";
		return;
	number = str(recursiveSearch(time))
	print "number of misses is", number
#The goal is to count the number of deadline misses that occur after the cutoff time.
#the cutoff time is defined close to the end of the timulation time (eg at 90% of the total simulation time).
#To count, we use a dichotomic search.
#Maybe ther eexist a built in python function to do it, but I didn't find it...
def recursiveSearch(timeArray):
	if (len(timeArray) == 0):
		return 0;
	if (len(timeArray) == 1):
		if (timeArray[0] < cutoffTime):
			return 0;
		else:
			return 1;
	if (timeArray[len(timeArray)/2] < cutoffTime):
		return recursiveSearch(timeArray[len(timeArray)/2:len(timeArray)-1])
	else:
		return recursiveSearch(timeArray[0:len(timeArray)/2-1]) + len(timeArray)/2


if __name__ == '__main__':
	main()





