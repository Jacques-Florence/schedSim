#!/bin/sh
rm actionValues*

cd configuration
rm -f ./*.sconf
python ./confGeneration.py configuration.conf parametricConfig.pconf
cd ..

rm -f reports/*
rm -f processes.txt

for f in configuration/*.sconf
do
	./simulation $f
done
for f in configuration/*.sconf
do
	python analysis/miss.py reports/${f##*/}deadlineMissesReport.txt
done
