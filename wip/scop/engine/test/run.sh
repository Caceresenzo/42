for file in engine/test/*.cpp; do
	echo Running $file
	if g++ $file engine/exception/*.cpp -I.; then
		if ./a.out; then
			echo OK
		else
			exit 1
		fi
	else
		exit 1
	fi
done