clang++ -I./tests/ *.cpp ./tests/$1.cpp -o test

cat ./tests/1992*.log | cut -f2- -d] > should_output.txt
./test | cut -f2- -d] > user_output.txt

diff should_output.txt user_output.txt

rm -f should_output.txt user_output.txt
