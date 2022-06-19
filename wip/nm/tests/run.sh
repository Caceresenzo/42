set -e

make -s -C tests list-files | grep -v make | while read -r file
do
#	sh tests/test.sh $file
	
#	for flag in "-a" "-u" "-g" "-r" "-p" "-ap" "-ar" "-up" "-ur" "-gp" "-gr"; do
	for flag in "-p" "-ap" "-up" "-gp"; do
		sh tests/test.sh $flag $file
	done
done
