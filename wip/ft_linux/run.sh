if test -f .env-state
then
	source .env-state
fi

function run() {
	script=$1
	number=$(basename $script | awk -F . '{ print $1 }')
	file=$(basename $script | awk -F . '{ print $2 }')

	if test -f .last && test $number -le "$(cat .last)"
	then
		. ./scripts/helper/wrap.sh $file ./scripts/helper/skip.sh
		return
	fi

	. ./scripts/helper/wrap.sh $file $script
	source .env-state

	echo $number > .last
}

for file in scripts/*.sh
do
	run $file
done
