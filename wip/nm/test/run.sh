#set -e

COMPILED_DIRECTORY=test/compiled

cd $COMPILED_DIRECTORY

function do_test() {
	echo "Running: $@"
	
	nm $@ >/tmp/nm.output 2>&1
	nm_exit=$?
	
	../../ft_nm $@ >/tmp/ft_nm.output 2>&1
	ft_nm_exit=$?
	
	cat /tmp/nm.output | sed 's/nm:/PROGRAM:/g' > /tmp/nm.anonimized.output
	cat /tmp/ft_nm.output | sed 's/ft_nm:/PROGRAM:/g' > /tmp/ft_nm.anonimized.output
	
	if ! diff /tmp/nm.anonimized.output /tmp/ft_nm.anonimized.output; then
		echo DIFF
		exit 1
	fi
	
	if ! test "$nm_exit" = "$ft_nm_exit"; then
		echo EXIT "$nm_exit" != "$ft_nm_exit"
		exit 1
	fi
}

for file in *; do
	do_test $file
	
	for flag in "-a" "-u" "-g" "-r" "-p" "-ap" "-ar" "-up" "-ur" "-gp" "-gr"; do
		do_test $flag $file
	done
done