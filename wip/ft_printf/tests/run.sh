echo "usage: sh run.sh [small]"

files="../libft/libft.a -g ../ft_*.c ./ft_printf_debugger.c"

if [ "$1" == "small" ]
then
	cmd="gcc -I../ -I../libft/ $files main_small.c -w -o a.out"
else
	cmd="gcc -I../ -I../libft/ $files main.c -w -o a.out"
fi

echo $cmd
$cmd

 ./a.out