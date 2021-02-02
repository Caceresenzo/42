DIRECTORY=$1
EXECUTABLE=$2

function bar()
{
	printf "\n\e[44m%s\e[K\e[0m\n" "$(date)"
}

printf "Executing %s with auto restart on directory %s file changes\n" "$EXECUTABLE" "$DIRECTORY"
bar

while true; do
	while true; do
		if [ -f "$EXECUTABLE" ]; then
			break
		fi
		
		sleep 0.5
	done

	$EXECUTABLE &
	
	disown
	
	watch -n 1 -c -g -d find . $DIRECTORY -type d -exec ls -l {} \\\; > /dev/null 2> /dev/null
	
	sleep 1
	
	if kill -9 $(pidof $(basename $EXECUTABLE)) > /dev/null 2> /dev/null; then
		printf "\n\e[41m%s\e[K\e[0m" "KILLED"
	fi
	
	bar
done