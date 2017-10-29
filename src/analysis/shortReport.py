#!/usr/bin/env python

import os
import re
import sys
import itertools

def main():
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
				print "running time = ", runningTime
			
	reportsFolder = "scratch"
	agingFilename = reportsFolder + "/" + configFilename + "instantaneousAgingReport.txt"
	reportFilename = reportsFolder + "/" + configFilename + "shortReport.txt"
	resultfile = "data/" + configFilename
	
	with open(reportFilename, 'a') as f:
		f.write("hello from " + reportFilename + "\n")

	deadlineMisses(reportsFolder, configFilename, reportFilename, runningTime)
	temperature(reportsFolder, configFilename, reportFilename);

def deadlineMisses(reportsFolder, configFilename, reportFilename, runningTime):
	ratio = 0.999
	missFilename = reportsFolder + "/" + configFilename + "deadlineMissesReport.txt"
	with open(missFilename) as f:
		with open(reportFilename, "a") as res:
			f.readline() #discard first line
			entries = [[float(elem) for elem in line.split(":")] for line in f]
			if len(entries) == 0:
				print "miss ok"
				res.write("deadline misses OK\n");
			else:
				if entries[len(entries)-1][0] < runningTime*ratio:
					print "miss ok"
					res.write("deadline misses OK\n");
				else:
					res.write("deadline misses FAIL\n");
					print "MISS FAIL"
					(time, pid) = itertools.izip(*entries)
					missNumber = str(recursiveSearch(time, ratio*runningTime))
					res.write("number of misses: " + str(missNumber))




#	with open(agingFilename) as f:
#		f.readline()
#		#entries = [[float(elem) for elem in line.split(":") if (len(elem) == 2 and float(elem[0]) > 0.9*runningTime)] for line in f if line != ""]
#		entries = [[float(elem) for elem in line.split(":")] for line in f if line != ""]
#		entries = [e for e in entries if e[0] > 0.9*runningTime]
#		print "entries are listed"
#		print "there are ",len(entries) , " entries"
#		print "entries[0] = ", entries[0]
#		(time, agingIncrements) = itertools.izip(*entries)
#		print "time and aging separated"
#		#index = len(time) - recursiveSearch(time, 0.9*runningTime);
#		#print "index is ", index
#		#agingIncrements = agingIncrements[index:len(agingIncrements)-1]
#		cumul = []
#		for e in agingIncrements:
#			if (len(cumul) == 0):
#				cumul.append(float(e))
#			else:
#				cumul.append(cumul[len(cumul)-1] + float(e))
#		with open(resultfile, 'a') as res:
#			if len(cumul) > 0:
#				res.write(configFilename + str(cumul[len(cumul)-1]) + "\n")
#			else:
#				res.write(configFilename + "Problem: cumul is empty\n")

#	with open(agingFilename) as f:
#		f.readline()
#		cumul = []
#		for line in f:
#			if (line == ""):
#				continue;
#			entry = line.split(":")
#			if (len(cumul) == 0):
#				cumul.append(float(entry[1]))
#			else:
#				if (len(entry) != 2):
#					print "line is:", line;
#				cumul.append(cumul[len(cumul)-1] + float(entry[1]))
#		with open(resultfile, 'a') as res:
#			if len(cumul) > 0:
#				res.write(configFilename + str(cumul[len(cumul)-1]) + "\n")
#			else:
#				res.write(configFilename + "Problem: cumul is empty\n")

def temperature(reportsFolder, configFilename, reportFilename):
	tempFilename = reportsFolder + "/" + configFilename + "temperatureReport.txt"
	with open(tempFilename) as f, open(reportFilename, 'a') as shortReportFile:
		f.readline() #discard first line
		entries = [[float(elem) for elem in line.split(":")] for line in f]
		size = len(entries)
		if size == 0:
			print "TEMPERATURE ERROR"
			shortReportFile.write("TEMPERATURE ERROR\n")
		temps = [e[1] for e in entries]
		maxTemp = max(temps)
		print "maximum temperature reached:", maxTemp
		shortReportFile.write("maximum temperature reached: " + str(maxTemp) + "\n")
		try:
			os.remove(tempFilename)
		except OSError:
			pass

#The goal is to count the number of deadline misses that occur after the cutoff time.
#the cutoff time is defined close to the end of the timulation time (eg at 90% of the total simulation time).
#To count, we use a dichotomic search.
#Maybe ther eexist a built in python function to do it, but I didn't find it...
def recursiveSearch(timeArray, cutoffTime):
	if (len(timeArray) == 0):
		return 0;
	if (len(timeArray) == 1):
		if (timeArray[0] < cutoffTime):
			return 0;
		else:
			return 1;
	halflen = len(timeArray)/2
	#print "timeArray[halflen] =", str(timeArray[halflen])
	if (timeArray[halflen] < cutoffTime):
		retval =  recursiveSearch(timeArray[halflen+1:len(timeArray)], cutoffTime)
		return retval
	else:
		retval = recursiveSearch(timeArray[0:halflen], cutoffTime) + len(timeArray[halflen:len(timeArray)])
		return retval


if __name__ == '__main__':
	main()


