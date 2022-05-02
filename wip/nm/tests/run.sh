#set -e

make -C tests list-files | grep -v make | while read -r file
do
	sh tests/test.sh tests/$file
	
	for flag in "-a" "-u" "-g" "-r" "-p" "-ap" "-ar" "-up" "-ur" "-gp" "-gr"; do
		sh tests/test.sh $flag tests/$file
	done
done
