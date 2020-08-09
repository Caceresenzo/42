current=$(pwd)

for f in ex*
do
	echo Trying to compile $f...
	cd $current/$f
	clang++ -Wall -Werror -Wextra -std=c++98 -g3 *.cpp

	if [ ! -f "$current/$f/a.out" ];
	then
		echo FAILED: a.out file not found
	else
		echo OK
	fi

	echo
done

cd $current
find . -name "a.out" | sort
