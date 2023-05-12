#!/bin/bash

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No color

# clear screen and checkout to the right folder (AP_Threads).
clear
cd ..
echo -e "${BLUE}[Test]${NC} Start Test Script for Enctypt and Decrypt" 
echo -e "${BLUE}[Test]${NC}     1. Messure the time it takes to encrypt chosen file to data/tmp.txt (encrypt with key = 5)."
echo -e "${BLUE}[Test]${NC}     2. Messure the time it takes to decrypt data/tmp.txt to data/result.txt (encrypt with key = 5)."
echo -e "${BLUE}[Test]${NC}     3. Compare data/resualt.txt and Source file.."
echo -e ""


# Creating the Executable using make.
make


# get the arguments
key="5"
flag="-e"
output_file="data/tmp.txt"
if [ "$1" -eq 1 ]; then
    input_file="data/helloWorld.txt"
elif [ "$1" -eq 2 ]; then
    input_file="data/az.txt"
elif [ "$1" -eq 3 ]; then
    input_file="data/bigFile.txt"
else
    echo -e "${BLUE}[Test]${NC} ${RED}Invalid argument!${NC} Please enter 1, 2, or 3."
    exit 1
fi

# Save the source file.
src_file=${input_file}

echo -e ""

# measure how long it took to run
time_taken=$( TIMEFORMAT='%3R'; { time ./coder "$key" "$flag" "$input_file" "$output_file"; } 2>&1 )

# print the result
echo -e "${BLUE}[Test]${NC} ${input_file} was encrypted with key 5 into ${output_file}."
echo -e "${BLUE}[Test]${NC} Time taken to encrypt: ${GREEN}${time_taken} seconds.${NC}"

# get the arguments
key="5"
flag="-d"
output_file="data/result.txt"
input_file="data/tmp.txt"
echo ""

# measure how long it took to run
time_taken=$( TIMEFORMAT='%3R'; { time ./coder "$key" "$flag" "$input_file" "$output_file"; } 2>&1 )

# print the result
echo -e "${BLUE}[Test]${NC} ${input_file} was decrypted with key 5 into ${output_file}."
echo -e "${BLUE}[Test]${NC} Time taken to decrypt: ${GREEN}${time_taken} seconds.${NC}"
echo -e ""


# Check if the output file is equal to the src file.
if cmp -s ${src_file} ${output_file};
then
    echo -e "${BLUE}[Test]${NC} Result: ${GREEN}The files are the same.${NC}"
else
    echo -e "${BLUE}[Test]${NC} Result: ${RED}The files are different.${NC}"
fi
echo ""


# Clean all the created files.
make clean
echo ""

# End Test.
echo -e "${BLUE}[Test]${NC} Test end."
echo -e "${BLUE}[Test]${NC} Out."

