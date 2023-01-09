for file in test/*.cpp; do
	echo Running $file
	if g++ $file source/lang/*.cpp -Isource/; then
		if ./a.out; then
			echo OK
		else
			exit 1
		fi
	else
		exit 1
	fi
done