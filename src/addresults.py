import re
import sys

if len(sys.argv) != 2:
	print "need one argument"

infile = open(sys.argv[1])
#get the configuration number
matched = re.match(r'[^0-9]+([0-9]+)[^0-9]+', sys.argv[1])
if (not matched):
	print "an error occured"
confNumber = matched.group(1)
confNumber = int(confNumber)

#get the number of misses
firstline = infile.readline()
matched = re.match(r'[^0-9]+([0-9]+)[^0-9]+', firstline)
if (not matched):
	print "an error occured"
nbMisses = matched.group(1)
nbMisses = int(nbMisses)


#determine if that config is good or not
res = ""
if (nbMisses == 0):
	res = "++"
elif (nbMisses < 1000):#this 1000 is too arbitrary...
	res = "+"
else:
	res = "-"

#write results back
results = open("configuration/results.txt", 'r+')
lines = results.readlines()
lines[confNumber-1] = lines[confNumber-1].rstrip('\n') + " " + res + "\n"
results.seek(0)
results.writelines(lines)





