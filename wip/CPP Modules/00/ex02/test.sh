file=./tests/tests_$1.cpp

if test -f "$file"; then
	clang++ -Werror -Wall -Wextra -std=c++98 -I./tests/ *.cpp $file -o test
	
	cat ./tests/1992*.log | cut -f2- -d] > should_output.txt
	./test | cut -f2- -d] > user_output.txt
	
	diff should_output.txt user_output.txt
	
	rm -f should_output.txt user_output.txt
else
	echo File \'$file\' does not exists.
	exit 1
fi