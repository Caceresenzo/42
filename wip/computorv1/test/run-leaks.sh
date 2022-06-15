#!/bin/bash

CASES_DIRECTORY=$1
EXPECTED_EXIT_CODE=$2

LOCATION_RIGHT_80=$(printf '\033[80G')
LOCATION_RIGHT_90=$(printf '\033[90G')
COLOR_RED=$(printf '\033[31m')
COLOR_GREEN=$(printf '\033[32m')
COLOR_CYAN=$(printf '\033[36m')
COLOR_RESET=$(printf '\033[0m')

for file in $CASES_DIRECTORY/*
do
	name=$(basename "$file")
	replaced=$(echo "$name" | sed 's/×/*/g' | sed "s/'//g")
	
	printf "%s%s%s" "$COLOR_CYAN" "$name" "$COLOR_RESET"
	
	valgrind ./computor "$replaced" >/tmp/valgrind_computor_output 2>&1
	
	
	if grep -oP "All heap blocks were freed" /tmp/valgrind_computor_output >/dev/null;
	then
		printf "$LOCATION_RIGHT_80$COLOR_GREEN%s$LOCATION_RIGHT_90%s$COLOR_RESET\n" "PASS" "All heap blocks were freed"
	else
		output=$(grep -oP "in use at exit: (\K.*)$" /tmp/valgrind_computor_output)
		printf "$LOCATION_RIGHT_80$COLOR_RED%s$LOCATION_RIGHT_90%s$COLOR_RESET\n" "FAIL" "$output"
	fi
done
