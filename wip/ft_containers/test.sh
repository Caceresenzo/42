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
C_IGNORED=$C_LIGHT_GRAY
C_CATEGORY=$C_LIGHT_YELLOW
C_TEST=$C_LIGHT_MAGENTA
C_TEST_FILE=$C_LIGHT_CYAN
C_PASS=$C_LIGHT_GREEN
C_FAIL=$C_LIGHT_RED

TEST_DIR=tests
CONTAINERS_DIR=$TEST_DIR/containers

TEST_STD=0
NOTIFY_WHICH=0
CONTAINERS=

while [[ "$#" -gt 0 ]]; do
    case $1 in
        -s|--std) TEST_STD=1 ;;
        -n|--std) NOTIFY_WHICH=1 ;;
        -c|--std) CONTAINERS=$2; shift ;;
        *) echo "Unknown parameter: $1"; exit 1 ;;
    esac
    shift
done

for container_path in $CONTAINERS_DIR/*
do
	container=$(basename "$container_path")
	printf $C_TREE". "$C_CONTAINER"%s"$C_RESET"\n" "$container"
	
	if [[ ! -z "$CONTAINERS" ]]; then
		if [[ $container != *"$CONTAINERS"* ]]; then
			printf $C_TREE"   |-- "$C_IGNORED"ignored..."$C_RESET"\n"
			continue
		fi
	fi

	for category_path in $container_path/*
	do
		category=$(basename "$category_path")
		printf $C_TREE"   |-- "$C_CATEGORY"%s"$C_RESET"\n" "$category"

		for test_file in $category_path/*.cpp
		do
			test=$(basename "$test_file")
			test_name=$(echo $test | awk -F . '{ print $1 }')
			test_success=$(echo $test | awk -F . '{ print $2 }')
			test_bin=/tmp/"$test".out
			
			printf $C_TREE"   |    |-- "$C_TEST"Compiling "$C_TEST_FILE"%s"$C_TEST"..."$C_RESET "$test"
			
			clang++ -ferror-limit=1 -std=c++98 -g3 -fsanitize=address -Wall -Wextra -Werror -I. -Itests/support -DTEST_USE_STD=$TEST_STD -DNOTIFY_WHICH=$NOTIFY_WHICH $test_file -o $test_bin
			compiled_exit_code=$?

			expected_exit_code=0
			if [ $test_success = "fail" ]; then
				expected_exit_code=1
			fi

			if [ $compiled_exit_code = $expected_exit_code ]; then
				printf $C_SAME_LINE$C_TREE"   |    |-- "$C_TEST"Testing "$C_TEST_FILE"%s"$C_TEST"..."$C_RESET" "$C_FAIL "$test_name"
				
				if $test_bin; then
					printf $C_PASS"OK"$C_RESET"\n"
				fi
			else
				if [ $test_success = "fail" ]; then
					printf $C_FAIL"FAIL (to not compile)"$C_RESET"\n"
				else
					printf $C_FAIL"FAIL (to compile)"$C_RESET"\n"
				fi
				
				exit 1
			fi
		done
		
		printf $C_TREE"   |"$C_RESET"\n"
	done
done
