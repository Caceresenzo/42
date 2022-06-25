set -e

make -C tests

make -s -C tests list-files | grep -v make | while read -r file
do
	sh tests/test.sh $file
	
	for flag in "-a" "-u" "-g" "-r" "-p" "-ap" "-ar" "-n" "-nr" "-up" "-ur" "-gp" "-gr" "-ag"; do
		sh tests/test.sh $flag $file
	done
done
