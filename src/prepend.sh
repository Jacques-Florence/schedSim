#!/usr/bin/env bash

shopt -s globstar
for i in **/*.cpp; do
	cat ../license.h "$i" > tmp
	mv tmp "$i"
done
