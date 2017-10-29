import matplotlib.pyplot as plt

print "hello world"

f = open("reports/temperatureReport.txt")
line = f.readline()
print line
time = []
temp = []
for line in f:
	entry = line.split(":")
	time.append(float(entry[0]))
	temp.append(float(entry[1]))
f.close()


plt.plot(time, temp, 'ro')
plt.show()
