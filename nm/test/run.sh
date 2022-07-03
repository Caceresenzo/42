set -e

make -C test

make -s -C test list-files | grep -v make | while read -r file
do
	sh test/test.sh $file
	
	for flag in "-a" "-u" "-g" "-r" "-p" "-ap" "-ar" "-n" "-nr" "-up" "-ur" "-gp" "-gr" "-ag"; do
		sh test/test.sh $flag $file
	done
done
