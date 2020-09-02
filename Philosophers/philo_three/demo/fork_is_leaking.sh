gcc -Wall -Wextra -Werror -o fork_is_leaking fork_is_leaking.c

function leaks_check()
{
	sleep 1

	pids=$(pidof fork_is_leaking)

	for pid in $pids; do
		echo "----- PROCESS #$pid -----"
		leaks $pid | tail -n +21
	done

	kill -9 $pids
}

leaks_check &

./fork_is_leaking

exit 0