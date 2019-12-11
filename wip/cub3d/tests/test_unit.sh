reset
rm -f *.bmp

executable=Cub3D

g_test_count=0
g_test_success_count=0
g_bmp_files_present=0
g_norm_passed=1

function norm()
{
	files="*.[ch]"
	result=$(norminette $files 2>&1)
	echo "import re" > py_norm.py
	echo "out = '''$result'''" >> py_norm.py
	echo "matches = re.finditer(r'Norme: (.*?)\$[\\\\n]{0,1}Error', out, re.MULTILINE)" >> py_norm.py
	echo "for match in matches:" >> py_norm.py
	echo "	print(match.group(1))" >> py_norm.py
	with_error=$(python3 py_norm.py)
	rm py_norm.py	
	for file in $files
	do
		printf "\033[4G%s\033[10G\033[0;36m'%s'" "🔎" $file
		if echo $with_error | grep -e $file > /dev/null
		then
			printf "\033[90G%s\033[94G\033[0;31m %s\033[0m\n" "❌"
			g_norm_passed=0
		else
			printf "\033[90G%s\033[94G\033[0;32m %s\033[0m\n" "✅"
		fi
	done
}

function check()
{
	local files=$1
	local shoud_exit_with=$2
	local flags=$3
	local timeout=$4
	local allow_timeout=$5
	
	for file in $files
	do
		g_test_count=$((g_test_count+1))
		printf "\033[4G%s\033[10G\033[0;36m'%s'" "🔎" "$file"
		{ ./$executable $file $flags ; } &> /dev/null &
		pid=$!
		loop=0
		forced=0
		while ps | grep -e "$executable" | grep -v grep > /dev/null
		do
			sleep 0.1
			loop=$((loop+1))
			if [ $loop == $timeout ]
			then
				kill -9 $(ps | grep -e "$executable" | grep -v grep | cut -c-5)
				signal=0
				forced=1
			fi
		done
		if [ $forced -ne 1 ]
		then
			wait $pid
			signal=$?
		fi
		if [ $forced -eq 1 ] && [ $allow_timeout = false ]
		then
			signal=142 # Timeout
		fi
		if [ $signal -eq $shoud_exit_with ]
		then
			g_test_success_count=$((g_test_success_count+1))
			printf "\033[90G%s\033[94G\033[0;32m %s\033[0m\033[0m" "✅" "SUCCESS"
			if [ $forced -eq 1 ]
			then
				printf "\033[110G(> %dms) " $((timeout*100))
			fi
			printf "\033[0m\n"
		else
			err="FAILED"
			if [ $signal -eq 134 ]
			then
				err="ABORT"
			elif [ $signal -eq 138 ]
			then
				err="BUS ERROR"
			elif [ $signal -eq 139 ]
			then
				err="SEG. FAULT"
			elif [ $signal -eq 142 ]
			then
				if [ $forced -eq 1 ]
				then
					err="FORCED TIMEOUT"
				else
					err="TIMEOUT"
				fi
			fi
			printf "\033[90G%s\033[94G\033[0;31m %s\033[0m" "❌" "$err"
			printf "\033[110G[expected %d, but got %d]\033[0m\n" "$shoud_exit_with" "$signal"
		fi
	done
}

function check_bmp_files()
{
	count=$(ls -l *.bmp | wc -l | tr -d " ")
	if [ $count -ge 1 ]
	then
		g_bmp_files_present=1
		printf "\033[90G%s\033[94G\033[0;32m %s\033[0m\n" "✅"
	else
		printf "\033[90G%s\033[94G\033[0;31m %s\033[0m\n" "❌"
	fi
}

function show_final_score()
{
	printf "\033[0G\033[0;97mFinal score: $g_test_success_count / $g_test_count \033[0m\033[90G"
	if [ $g_test_count -eq $g_test_success_count ] && [ $g_norm_passed -eq 1 ]
	then
		printf "👌\n"
	else
		printf "💥\n"
	fi
}

echo "\n\033[0G\033[0;97mChecking norm\033[0m\n"
norm

echo "\n\033[0G\033[0;97mTesting valid map\033[0m\n"
check "./tests/maps/scene_valid_*" 0 "" 15 true

echo "\n\033[0G\033[0;97mTesting valid map (with -save flag)\033[0m\n"
check "./tests/maps/scene_valid_*" 0 "-save" 80 true

printf "\033[4G%s\033[10G\033[0;36mChecking BMP files..." "🔎"
check_bmp_files

echo "\n\033[0G\033[0;97mTesting invalid map\033[0m\n"
check "/i/dont/exists ./tests/maps/scene_broken*.cub" 1 "" 15 false

echo ""
show_final_score