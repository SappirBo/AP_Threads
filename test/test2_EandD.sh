#!/bin/bash

# clear screen and checkout to the right folder (AP_Threads).
clear
cd ..
echo "[Test] Start Test Script 1 - Only enctypt - src file to dest file" 
echo ""


# Creating the Executable using make.
make


# get the arguments
key="5"
flag="-e"
output_file="data/result.txt"
if [ "$1" -eq 1 ]; then
    input_file="data/helloWorld.txt"
elif [ "$1" -eq 2 ]; then
    input_file="data/az.txt"
elif [ "$1" -eq 3 ]; then
    input_file="data/bigFile.txt"
else
    echo "[Test] Invalid argument. Please enter 1, 2, or 3."
    exit 1
fi
echo ""

# measure how long it took to run
time_taken=$( TIMEFORMAT='%3R'; { time ./coder "$key" "$flag" "$input_file" "$output_file"; } 2>&1 )

# print the result
echo "[Test] Time taken to encrypt: ${time_taken} seconds"
echo ""

# get the arguments
key="5"
flag="-d"
output_file="data/result.txt"
input_file="data/result.txt"
echo ""

# measure how long it took to run
time_taken=$( TIMEFORMAT='%3R'; { time ./coder "$key" "$flag" "$input_file" "$output_file"; } 2>&1 )

# print the result
echo "[Test] Time taken to decrypt: ${time_taken} seconds"
echo ""


make clean
echo ""

echo "[Test] Test end."


