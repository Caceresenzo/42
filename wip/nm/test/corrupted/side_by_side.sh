NM_OUTPUT=/tmp/nm.output
FT_NM_OUTPUT=/tmp/ft_nm.output

COLOR_RED=$(printf '\033[31m')
COLOR_GREEN=$(printf '\033[32m')
COLOR_CYAN=$(printf '\033[36m')
COLOR_RESET=$(printf '\033[0m')

function run()
{
	path=$1
	name=$(echo $path | sed 's+saved/++g' | sed 's+//+/+g')
	
	width="$(tput cols)"
	
	printf "\n${COLOR_GREEN}Running %s$COLOR_RESET\n" "$name"
	printf "${COLOR_CYAN}-%.0s$COLOR_RESET" $(seq 1 $width)
	
	nm -agp "$path" >$NM_OUTPUT 2>&1
	echo -e "status=$?" >>$NM_OUTPUT
	
	./../../ft_nm -agp "$path" >$FT_NM_OUTPUT 2>&1
	echo -e "status=$?" >>$FT_NM_OUTPUT
	
	pr -m -t -v -w $width -S"  $COLOR_CYAN|$COLOR_RESET  " $NM_OUTPUT $FT_NM_OUTPUT
}

for program in saved/*/;
do
	for description in "$program/"*;
	do
		run "$description"
	done
done
