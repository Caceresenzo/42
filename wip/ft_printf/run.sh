echo "usage: sh run.sh [small]"

files="./libft/libft.a -g ft_*.c"

if [ "$1" == "small" ]
then
	cmd="gcc $files main_small.c -w -o a.out"
else
	cmd="gcc $files main.c -w -o a.out"
fi

echo $cmd
$cmd

 ./a.out