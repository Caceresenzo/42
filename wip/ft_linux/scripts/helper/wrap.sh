prefix=$1
shift

{
	set -e
	. ./$@ 2>&1
	export > .env-state
} | awk '$0="[\33[31m'$prefix'\33[0m] "$0'

exit_code=${pipestatus[1]}

if test $exit_code -ne 0
then
	exit $exit_code
fi
