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
FSANITIZE=0
VALGRIND=0
ERROR_LIMIT=1
CONTAINERS=
CATEGORIES=
TESTS=
COMPILER=g++

function print_help()
{
	echo "ft_containers testing script"
	echo " (by ecaceres, tests are adapted from official libc++ repository)"
	echo
	echo
	echo " -s, --std"
	echo "    use std:: instead of ft::"
	echo
	echo " -n, --notify"
	echo "    notify with a compiler warning which namespace will be used"
	echo
	echo " -c, --container <name>"
	echo "    specify container to test (all if none is provided)"
	echo
	echo " -k, --category <name>"
	echo "    specify category to test (all if none is provided)"
	echo
	echo " -t, --test <name>"
	echo "    specify test to do (all if none is provided)"
	echo
	echo " -f, --fsanitize"
	echo "    compile with -fsanitize=address"
	echo
	echo " -v, --valgrind"
	echo "    run with valgrind"
	echo
	echo " -l, --error-limit <value>"
	echo "    compile with -ferror-limit=<value> (default: 1)"
	echo
	echo " -C, --compiler <executable>"
	echo "    change compiler (default: g++)"
	echo
	echo " -h, --help"
	echo "    display this help message"
}

while [[ "$#" -gt 0 ]]; do
    case $1 in
        -s|--std) TEST_STD=1 ;;
        -n|--notify) NOTIFY_WHICH=1 ;;
        -c|--container) CONTAINERS+="$2 "; shift ;;
        -k|--category) CATEGORIES+="$2 "; shift ;;
        -t|--test) TESTS+="$2 "; shift ;;
        -f|--fsanitize) FSANITIZE=1 ;;
        -v|--valgrind) VALGRIND=1 ;;
        -l|--error-limit) ERROR_LIMIT=$2; shift ;;
        -C|--compiler) COMPILER=$2; shift ;;
        -h|--help) print_help; exit 0 ;;
        *) echo "unknown parameter: $1"; echo "use --help for more info"; exit 1 ;;
    esac
    shift
done

for container_path in $CONTAINERS_DIR/*
do
	container=$(basename "$container_path")
	printf $C_TREE". "$C_CONTAINER"%s"$C_RESET"\n" "$container"
	
	if [[ ! -z "$CONTAINERS" ]]; then
		if [[ " $CONTAINERS " != *" $container "* ]]; then
			printf $C_TREE"   |-- "$C_IGNORED"ignored..."$C_RESET"\n"
			continue
		fi
	fi

	for category_path in $container_path/*
	do
		category=$(basename "$category_path")
		printf $C_TREE"   |-- "$C_CATEGORY"%s"$C_RESET"\n" "$category"
		
		if [[ ! -z "$CATEGORIES" ]]; then
			if [[ " $CATEGORIES " != *" $category "* ]]; then
				printf $C_TREE"   |    |-- "$C_IGNORED"ignored..."$C_RESET"\n"
				continue
			fi
		fi

		for test_file in $category_path/*.cpp
		do
			test=$(basename "$test_file")
			test_name=$(echo $test | awk -F . '{ print $1 }')
			test_success=$(echo $test | awk -F . '{ print $2 }')
			test_bin=/tmp/"$test".out
			
			if [[ ! -z "$TESTS" ]]; then
				if [[ " $TESTS " != *" $test_name "* ]]; then
					printf $C_TREE"   |    |-- "$C_IGNORED"ignored "$C_TEST_FILE"%s"$C_TEST"..."$C_RESET"\n" "$test_name"
					continue
				fi
			fi
			
			printf $C_TREE"   |    |-- "$C_TEST"Compiling "$C_TEST_FILE"%s"$C_TEST"..."$C_RESET "$test"
			
			fsanitize_flag=
			if [[ $FSANITIZE = 1 ]]; then
				fsanitize_flag+="-fsanitize=address"
			fi
		
			compiler_error_limit_flag=
			if [[ $compiler = "clang++" ]]; then
				compiler_error_limit_flag+=-ferror-limit="$ERROR_LIMIT"
			elif [[ $compiler = "g++" ]]; then
				compiler_error_limit_flag+=-fmax-errors="$ERROR_LIMIT"
			fi
			
			$COMPILER $compiler_error_limit_flag -std=c++98 -g3 $fsanitize_flag -Wall -Wextra -Werror -I. -Itests/support -DTEST_USE_STD=$TEST_STD -DNOTIFY_WHICH=$NOTIFY_WHICH $test_file -o $test_bin
			compiled_exit_code=$?

			expected_exit_code=0
			if [ $test_success = "fail" ]; then
				expected_exit_code=1
			fi

			if [ $compiled_exit_code = $expected_exit_code ]; then
				printf $C_SAME_LINE$C_TREE"   |    |-- "$C_TEST"Testing "$C_TEST_FILE"%s"$C_TEST"..."$C_RESET" "$C_FAIL "$test_name"
				
				valgrind_exec=
				valgrind_parameters=
				if [[ $VALGRIND = 1 ]]; then
					valgrind_exec=valgrind
					valgrind_parameters=--leak-check=full
				fi
				
				if $valgrind_exec $valgrind_parameters $test_bin 2>&1; then
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
