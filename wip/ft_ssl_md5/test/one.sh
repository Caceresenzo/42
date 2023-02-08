command=$1
file=$2

${command}sum $file | awk '{ print $1 }' > /tmp/std
./ft_ssl $command $file > /tmp/ft

if diff /tmp/std /tmp/ft;
then
	printf "OK: case=%s\n" $(basename $file)
else
	printf "FAIL: case=%s\n" $(basename $file)
fi
