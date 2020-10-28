DIRECTORY=$1
EXECUTABLE=$2

function bar()
{
	printf "\n\e[44m%s\e[K\e[0m\n" "$(date)"
}

function do_watch()
{
	while kill -0 $PARENT_PID > /dev/null 2>&1; do
		watch -n 1 -c -g -d find $DIRECTORY -type f -exec ls -lT {} \\\; > /dev/null 2> /dev/null
	
		kill -9 $(pidof $(basename $EXECUTABLE)) > /dev/null 2> /dev/null
	done
	
	echo Watcher exited
}

printf "Executing %s with auto restart on directory %s file changes\n" "$EXECUTABLE" "$DIRECTORY"
bar

PARENT_PID=$$
do_watch &

while true; do
	while true; do
		if [ -f "$EXECUTABLE" ]; then
			break
		fi
		
		sleep 0.5
	done

	if $EXECUTABLE; then
		printf "\n\e[41m%s\e[K\e[0m" "EXIT"
	else
		printf "\n\e[41m%s\e[K\e[0m" "KILLED"
	fi
	
	sleep 1
	
	bar
done