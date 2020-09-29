for f in *.cpp; do
	executable=$(basename $f .cpp)

	echo Compiling $executable...
	clang++ -std=c++98 -Wall -Wextra -Werror -I../ $f -o $executable
done