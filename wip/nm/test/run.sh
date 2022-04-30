#set -e

for file in test/compiled/*; do
	bash test/test.sh $file
	
	for flag in "-a" "-u" "-g" "-r" "-p" "-ap" "-ar" "-up" "-ur" "-gp" "-gr"; do
		bash test/test.sh $flag $file
	done
done
