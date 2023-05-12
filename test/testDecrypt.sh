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
echo -e "${BLUE}[Test]${NC} Start Test Script for Decrypt" 
echo -e "${BLUE}[Test]${NC}     2. Messure the time it takes to decrypt data/tmp.txt to data/result.txt (encrypt with key = 5)."
echo -e ""


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
elif [ "$1" -eq 4 ]; then
    input_file="data/tmp.txt"
else
    echo -e "${BLUE}[Test]${NC} ${RED}Invalid argument!${NC} Please enter 1, 2, or 3."
    exit 1
fi



# measure how long it took to run
time_taken=$( TIMEFORMAT='%3R'; { time ./coder "$key" "$flag" "$input_file" "$output_file"; } 2>&1 )

# print the result
echo -e "${BLUE}[Test]${NC} ${input_file} was decrypted with key 5 into ${output_file}."
echo -e "${BLUE}[Test]${NC} Time taken to decrypt: ${GREEN}${time_taken} seconds.${NC}"
echo -e ""




# Clean all the created files.
make clean
echo ""