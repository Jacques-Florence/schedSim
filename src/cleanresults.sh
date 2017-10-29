#!/bin/sh



cat data/results.txt | grep "configuration" | sort | uniq > data/sorted


./getMissingFiles.py
