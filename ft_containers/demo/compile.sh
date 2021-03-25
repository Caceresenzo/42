for f in *.cpp; do
	executable=$(basename $f .cpp)

	echo Compiling $executable...
	g++ -std=c++98 -Wall -Wextra -Werror -I../ -g3 $f -o $executable # -fsanitize=address 
done
