#!/usr/bin/env python
import re
import shutil
import sys
import os

def main():
	if (len(sys.argv) != 3):
		print "two arguments needed: template config file and changes"
		sys.exit(0)
	templateFile = open(sys.argv[1])
	changesFile = open(sys.argv[2])
	tuples = []
	for line in changesFile:
		if (re.match(r'^#', line)):
			continue
		sectionMatch = re.match(r'\[(.+)\]', line)
		if (sectionMatch):
			currentSection = sectionMatch.group(1)
		entryMatch = re.match(r'(.+) += +(.+)', line)
		if (entryMatch):
			tuples.append((currentSection, entryMatch.group(1), (entryMatch.group(2)).split(" ")))

	nbParams = len(tuples)

	nbOfConfigs = 1
	lengths = [1]*nbParams
	for i in range(len(tuples)):

		lengths[i] = (len(tuples[i][2]))
		if (lengths[i] > 1000):
			print "Error: Only 1000 values swept allowed"
			sys.exit(-1)
		nbOfConfigs *= lengths[i]


	entries = []
	counter = 0
#there should be nbParams for_loops

	indexes = [0]*nbParams

	func(nbParams, 0, indexes, lengths, tuples, entries);


			

	counter = 1

	fileFormat = re.match(r'(.+)\.conf', sys.argv[1])
	stem = ""
	if fileFormat:
		stem = fileFormat.group(1)
	else:
		print "The template file must have extension .conf"


	for entry in entries:
		content = templateFile.readlines();
		for i in range(len(content)):
			if (re.match(r'^#', content[i])):
				continue;
			sectionMatch = re.match(r'\[(.+)\]', content[i])
			if (sectionMatch):
				currentSection = sectionMatch.group(1)
			entryMatch = re.match(r'(.+) += +(.+)', content[i])
			if (entryMatch):
				currentParam = entryMatch.group(1)
				for j in range(nbParams):
					if (entry[j] != None):
						if (currentSection == entry[j][0]):
							if (entry[j][1] == currentParam):
								content[i] = entry[j][1] + " = " + entry[j][2] + "\n"
		outfilename = stem
		outfilename += format(counter, '04d') + "__"
		for j in range(nbParams):
			outfilename += entry[j][1]
			try:
				temp = float(entry[j][2])
				outfilename += "{0:05f}".format(temp)
			except ValueError: #entry[][] can be a string parameter
				temp = entry[j][2]
				outfilename += temp
			outfilename += "_"
		outfilename += ".sconf"
		with open(outfilename, 'w') as outFile:
			outFile.writelines(content)
		with open("list", "a") as configslist:
			configslist.write(outfilename + "\n")
		counter += 1
		templateFile.seek(0)

	templateFile.close()
	changesFile.close()


def func(nbParams, p, indexes, lengths, tuples, entries):
	indexes[p] = 0;
	for i in range(max(1, lengths[p])):
		if p == (nbParams-1):
			entryTuples = [None]*nbParams;
			for var in range(nbParams):
				if (len(tuples) > var):
					entryTuples[var] = (tuples[var][0], tuples[var][1], tuples[var][2][indexes[var]])
			entry = []
			for j in range(nbParams):
				entry.append(entryTuples[j])
			#entries.append((entryTuples[0], entryTuples[1], entryTuples[2], entryTuples[3], entryTuples[4]))
			entries.append(entryTuples)		
		else:
			func(nbParams, p+1, indexes, lengths, tuples, entries);
		indexes[p] += 1;

if __name__ == '__main__':
	main()
























