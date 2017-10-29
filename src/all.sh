#!/bin/sh

rm *.out
rm *.txt
#rm data/*
rm scratch/*
cd configuration/
rm *.sconf
rm list
#./confGeneration.py configurationRL.conf parametricConfig.pconf
#./confGeneration.py configurationRMS.conf parametricConfig.pconf
./confGeneration.py configuration.conf parametricConfig.pconf
cd ..
for i in `seq 1 150`;
#for i in 3
do
	./generatePbs.py $i
	qsub "job$i.pbs"
	rm "job$i.pbs"
	sleep 10s
done
