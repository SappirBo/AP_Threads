#!/bin/bash

# clear screen and checkout to the right folder (AP_Threads).
clear
cd ..
echo "[Test] Start Test Script 1 - Only enctypt - src file to dest file" 
echo "[Test]                       Will messure the time it takes to encrypt chosen file (encrypt with key = 3)."
echo ""


# Creating the Executable using make.
make


# get the arguments
key="5"
flag="-e"
output_file="data/tmpResult.txt"
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

# Save the source file.
src_file=${input_file}

echo ""

# measure how long it took to run
time_taken=$( TIMEFORMAT='%3R'; { time ./coder "$key" "$flag" "$input_file" "$output_file"; } 2>&1 )

# print the result
echo "[Test] ${input_file} was encrypted with key 5 into ${output_file}."
echo "[Test] Time taken to encrypt: ${time_taken} seconds."
echo ""

# get the arguments
key="5"
flag="-d"
output_file="data/result.txt"
input_file="data/tmpResult.txt"
echo ""

# measure how long it took to run
time_taken=$( TIMEFORMAT='%3R'; { time ./coder "$key" "$flag" "$input_file" "$output_file"; } 2>&1 )

# print the result
echo "[Test] ${input_file} was decrypted with key 5 into ${output_file}."
echo "[Test] Time taken to decrypt: ${time_taken} seconds"
echo ""


# Check if the output file is equal to the src file.
if cmp -s ${src_file} ${output_file};
then
    echo "[Test] Result: The files are the same"
else
    echo "[Test] Result: The files are different"
fi
echo ""


# Clean all the created files.
make clean
echo ""

# End Test.
echo "[Test] Test end."

