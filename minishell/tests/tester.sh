COLOR_RESET="\e[0m"
COLOR_LIGHT_RED="\e[91m"
COLOR_LIGHT_GREEN="\e[92m"
COLOR_LIGHT_YELLOW="\e[93m"
COLOR_LIGHT_MAGENTA="\e[95m"
COLOR_WHITE="\e[97m"

RESULT_OFFSET="\e[80G"

PREFIX="$COLOR_LIGHT_MAGENTA[$COLOR_LIGHT_GREEN?$COLOR_LIGHT_MAGENTA]"

DIR=$(dirname $0)

rm -f $DIR/*.diff

passed_test=0
total_test=0

function print_no_end()
{
	printf "$PREFIX $COLOR_WHITE%s$COLOR_RESET" "$1"
}

function print()
{
	printf "$PREFIX $COLOR_WHITE%s$COLOR_RESET\n" "$1"
}

function do_test()
{
	file="$1"
	
	./minishell < "$file" 2>/dev/null | cat -e | head -n 1 &> $DIR/minishell_output
	minishell_exit=$?
	
	bash < "$file" 2>/dev/null | cat -e &> $DIR/bash_output
	bash_exit=$?
	
	diff $DIR/minishell_output $DIR/bash_output > $DIR/diff
	diff_exit="$?"
	
	if [ "$diff_exit" -ne 0 ]
	then
		printf "$RESULT_OFFSET[ $COLOR_LIGHT_RED%s$COLOR_RESET ] (%s)%s\n" "FAIL" "diff"
		mv $DIR/diff "$file.diff"
	elif [ "$minishell_exit" != "$bash_exit" ]
	then
		printf "$RESULT_OFFSET[ $COLOR_LIGHT_RED%s$COLOR_RESET ] (%s)%s\n" "FAIL" "exit code"
	else
		printf "$RESULT_OFFSET[ $COLOR_LIGHT_GREEN%s$COLOR_RESET ]\n" "PASS"
		passed_test=$((passed_test+1))
	fi
}

for file in $DIR/*.test
do
	print_no_end "Running $(basename $file | cut -f 1 -d '.')"
	total_test=$((total_test+1))
	do_test "$file"
done

print "Final score $passed_test / $total_test"

rm -f $DIR/minishell_output $DIR/bash_output
