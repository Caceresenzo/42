#set -e

COMPILED_DIRECTORY=test/compiled

cd $COMPILED_DIRECTORY

function do_test() {
	echo "Running: $@"
	
	nm $@ > /tmp/nm.output
	../../ft_nm $@ > /tmp/ft_nm.output
	
	if ! diff /tmp/nm.output /tmp/ft_nm.output; then
		echo DIFF
		exit 1
	fi
}


for file in *; do
	do_test $file
	
	for flag in "-a" "-u" "-r" "-p"; do
		do_test $flag $file
	done
done