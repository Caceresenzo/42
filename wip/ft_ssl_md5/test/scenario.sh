command=$1

RESET='\e[0m'
LIGHT_MAGENTA='\e[95m'

function execute()
{
	line=$1
	
	printf "> $LIGHT_MAGENTA%s$RESET\n" "$line"
	bash -c "$line"
}

function empty_line()
{
	echo
}

execute "echo \"42 is nice\" | openssl $command"
empty_line

execute "echo \"42 is nice\" | ${command}sum"
empty_line

execute "echo \"42 is nice\" | ./ft_ssl $command"
empty_line

execute "echo \"42 is nice\" | ./ft_ssl $command -p"
empty_line

execute "echo \"Pity the living.\" | ./ft_ssl $command -q -r"
empty_line

execute "echo \"And above all,\" > file"
execute "./ft_ssl $command file"
execute "./ft_ssl $command -r file"
empty_line

execute "./ft_ssl $command -s \"pity those that aren't following baerista on spotify.\""
empty_line

execute "echo \"be sure to handle edge cases carefully\" | ./ft_ssl $command -p file"
empty_line

execute "echo \"some of this will not make sense at first\" | ./ft_ssl $command file"
empty_line

execute "echo \"but eventually you will understand\" | ./ft_ssl $command -p -r file"
empty_line

execute "echo \"GL HF let's go\" | ./ft_ssl $command -p -s \"foo\" file"
empty_line

execute "echo \"one more thing\" | ./ft_ssl $command -r -p -s \"foo\" file -s \"bar\""
empty_line

execute "echo \"just to be extra clear\" | ./ft_ssl $command -r -q -p -s \"foo\" file"
empty_line

empty_line
empty_line

execute "echo \"https://www.42.fr/\" > website"
execute "./ft_ssl $command -q website"
execute "${command}sum website"
empty_line

execute "./ft_ssl $command -s \"42 is nice\""
execute "echo -n \"42 is nice\" | ${command}sum"
