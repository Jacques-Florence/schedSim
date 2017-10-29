#!/bin/sh

for f in configuration/*.sconf
do
	python addresults.py reports/${f##*/}deadlineMissesReport.txt
done



