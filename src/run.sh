#!/bin/bash


configname=configuration.conf
configfile="configuration/$configname"

verbosity='> /dev/null'
while [[ $# > 0 ]]
do
	key="$1"
	case $key in
		-verbose)
			verbosity=''
			;;
		-configNumber)
			confignumber=$2
			echo "confignumber is $confignumber"
			configfile="`head -$confignumber configuration/list | tail -1`"
			configfile="configuration/$configfile"
			shift
			;;
		-config)
			configfile = $2
			;;
		*)
			;;
	esac
	shift
done
configname=$(basename $configfile)

#rm -f *processes.txt
rm -f scratch/*$configname*
echo "the name of configfile is"
echo $configname
rm -f data/*$configname*
rm -f scratch/*$configname*
rm -f rlfile*
rm -f actionValues*
progname=bin/SchedulingSimulator
eval $progname $configfile $verbosity
gprof bin/SchedulingSimulator | gprof2dot -n 2 -s | dot -Tpng -o callgraph.png

#python analysis/miss.py
analysis/shortReport.py $(basename $configfile)

####rm scratch/$(basename $configfile)*Report.txt

#cat scratch/$(basename $configfile)shortReport.txt $configfile > data/$(basename $configfile)
#rm *.txt

#rm scratch/*$(basename $configfile)*

#rm scratch/*.out
#rm *.out
