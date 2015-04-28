#!/bin/bash
#I'm extraordinarily rusty on my scripting. The Lazy way it is.
cp ./Makefile ./bin/
cp -v src/driver.cpp bin/
cp -v src/HashMap.cpp bin/
cp -v include/HashMap.h bin/
cp -v docs/14ers.csv bin/

#for file in *.cpp; do
#	cp -v "$file" ..bin/"$file"
#done
echo "Files copied into ./bin"

