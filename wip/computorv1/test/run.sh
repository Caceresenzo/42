#!/bin/bash

CASES_DIRECTORY=$1
EXPECTED_EXIT_CODE=$2

LOCATION_RIGHT=$(printf '\033[90G')
COLOR_RED=$(printf '\033[31m')
COLOR_GREEN=$(printf '\033[32m')
COLOR_CYAN=$(printf '\033[36m')
COLOR_RESET=$(printf '\033[0m')

function print_outcome()
{
	color=$1
	text=$2
	
	printf "%s%s%s$COLOR_RESET\n" "$LOCATION_RIGHT" "$color" "$text"
}

for file in $CASES_DIRECTORY/*
do
	name=$(basename "$file")
	replaced=$(echo "$name" | sed 's/×/*/g' | sed "s/'//g")
	
	./computor "$replaced" > /tmp/computor_output 2>&1
	exit_code=$?
	
	printf "%s%s%s" "$COLOR_CYAN" "$name" "$COLOR_RESET"
	
	if [ $exit_code != $EXPECTED_EXIT_CODE ]
	then
		print_outcome "$COLOR_RED" "FAIL"
	else
		if diff --color=always --side-by-side --suppress-common-lines /tmp/computor_output "$file" > /tmp/computor_diff;
		then
			if [ "$EXPECTED_EXIT_CODE" = "0" ];
			then
				print_outcome "$COLOR_GREEN" "PASS"
			else
				print_outcome "$COLOR_GREEN" "XPASS"
			fi
		else
			print_outcome "$COLOR_RED" "DIFF FAIL"
			cat /tmp/computor_diff
		fi
	fi
done
