#!/usr/bin/env python
import matplotlib
#matplotlib.use('GTKAgg')
import matplotlib.pyplot as plt
import itertools

allSteps = False

def actionValuePlot(state, action):
	rootfilename = "actionValuesForState"
	print "Processing state", state, "...\n"
	filename = rootfilename + str(state) + "action" + str(action)
	with open(filename) as f:
		if allSteps:
			value = [float(line) for line in f]
			labl = str(state) + "-" + str(action)
			plt.plot(value, drawstyle='steps-post', label=labl)
		else:
			pair = [line.split(" ") for line in f]
			time = [float(elem[0]) for elem in pair]
			value = [float(elem[1]) for elem in pair]
			labl = str(state) + "-" + str(action)
			plt.plot(time, value, drawstyle='steps-post', label=labl)
			


def main():
	array = []
	with open("rlfile.txt") as f:
		splitlines = [line.rstrip().split(" ") for line in f]
		for line in splitlines:
			actions = [float(a) > -70000 for a in line]
			array.append(actions)
	#fig, ax = plt.subplots()
	#for state in (0, 1, 2, 3, 4, 5, 6, 7):
	for state in range(144):
		for action in range(3):
			if array[state][action]:
				actionValuePlot(state, action)
	plt.legend(loc='upper left', bbox_to_anchor=(1, 1), ncol=2, borderaxespad=0)
	plt.show()



if __name__ == '__main__':
	main()
