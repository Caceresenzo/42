set -e

while read -r file
do
	sh test/test.sh $file
	
	for flag in "-a" "-u" "-g" "-r" "-p" "-ap" "-ar" "-n" "-nr" "-up" "-ur" "-gp" "-gr" "-ag"; do
		sh test/test.sh $flag $file
	done
done <<EOF
./ft_nm ./ft_nm
./ft_nm asd
./ft_nm asd asd zxc $(which gcc).c
/dev/
/dev/zero
/dev/zero /dev/zero
/dev/zero /dev/zero /dev/
/dev/zero /dev/zero /dev/ ./ft_nm
/dev/zero /dev/zero /dev/ ./ft_nm asd
EOF
