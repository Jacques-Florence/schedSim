#!/usr/bin/env python
import matplotlib.pyplot as plt
import sys

filename = "scratch/configuration.confinstantaneousAgingReport.txt"
if (len(sys.argv) > 1):
	filename = sys.argv[1]

with open(filename) as f:
	print f.readline()
	time = []
	inst = []
	cumul = []
	for line in f:
#		if (len(inst) < 10000):
		entry = line.split(":")
		time.append(float(entry[0]))
		inst.append(float(entry[1]))
		if (len(cumul) == 0):
			cumul.append(float(entry[1]))
		else:
			cumul.append(cumul[len(cumul)-1] + float(entry[1]))

#f = open("reports/energyReport.txt")
#line = f.readline()
#time2 = []
#power = []
#for line in f:
#	entry = line.split(":")
#	time2.append(float(entry[0]))
#	power.append(float(entry[1]))
#f.close()


#avg = []
#buf = []
#bufindex = 0
#for i in range(0,20001):
#	buf.append(temp[i])
#for i in range (0,10000):
#	avg.append(0.0)
#sum = 0
#for i in range(0,20001):
#	sum += buf[i]
#avg.append(sum/20001)
#for i in range(10001, len(temp)-10000):
#	sum -= buf[bufindex]
#	buf[bufindex] = temp[i+10000]
#	sum += buf[bufindex]
#	avg.append(sum/20001)
#	bufindex += 1
#	if (bufindex == 20000):
#		bufindex = 0
#for i in range (len(temp)-10001,len(temp)-1):
#	avg.append(0)






#avg = []
#alpha = 0.0001
#avg.append(0.0)
#for i in range(1,len(temp)):
#	a = temp[i]*alpha + (1-alpha)*avg[i-1]
#	avg.append(a)


#plt.plot(time, inst, 'ro')
#plt.plot(time, cumul, 'bo')

print cumul[len(cumul)-1]

#plt.plot(time2, power, 'bo')
#plt.plot(time, avg, 'b-')
plt.show()
