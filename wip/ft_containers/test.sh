C_SAME_LINE="\033[1K\r"
C_RESET="\033[0m"

C_WHITE="\033[39m"

C_LIGHT_GRAY="\033[37m"
C_LIGHT_RED="\033[91m"
C_LIGHT_GREEN="\033[92m"
C_LIGHT_YELLOW="\033[93m"
C_LIGHT_MAGENTA="\033[95m"
C_LIGHT_CYAN="\033[96m"

C_TREE=$C_LIGHT_GRAY
C_CONTAINER=$C_LIGHT_YELLOW
C_CATEGORY=$C_LIGHT_YELLOW
C_TEST=$C_LIGHT_MAGENTA
C_TEST_FILE=$C_LIGHT_CYAN
C_PASS=$C_LIGHT_GREEN
C_FAIL=$C_LIGHT_RED

TEST_DIR=tests
CONTAINERS_DIR=$TEST_DIR/containers

for container_path in $CONTAINERS_DIR/*
do
	container=$(basename "$container_path")
	printf $C_TREE". "$C_CONTAINER"%s"$C_RESET"\n" "$container"

	for category_path in $container_path/*
	do
		category=$(basename "$category_path")
		printf $C_TREE"   |-- "$C_CATEGORY"%s"$C_RESET"\n" "$category"

		for test_file in $category_path/*
		do
			test=$(basename "$test_file")
			test_bin=/tmp/"$test".out
			
			printf $C_TREE"   |    |-- "$C_TEST"Compiling "$C_TEST_FILE"%s"$C_TEST"..."$C_RESET "$test"

			if clang++ -std=c++98 -g3 -fsanitize=address -I. -Itests/support $test_file -o $test_bin; then
				printf $C_SAME_LINE$C_TREE"   |    |-- "$C_TEST"Testing "$C_TEST_FILE"%s"$C_TEST"..."$C_RESET" "$C_FAIL "$(echo $test | awk -F . '{ print $1 }')"
				
				if $test_bin; then
					printf $C_PASS"OK"$C_RESET"\n"
				fi
			else
				printf $C_FAIL"FAIL (to compile)"$C_RESET"\n"
				exit 1
			fi
		done
		
		printf $C_TREE"   |"$C_RESET"\n"
	done
done
