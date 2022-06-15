TEMPORARY_FILE=/tmp/computor-test

COLOR_CYAN=$(printf '\033[36m')
COLOR_RESET=$(printf '\033[0m')

PREFIX="$COLOR_CYAN[creator]$COLOR_RESET"

type=$1
expression=$2

echo "$PREFIX running: ./computor '$expression' 2>&1"

./computor "$expression" 2>&1 | tee "$TEMPORARY_FILE"

echo -n "$PREFIX create test? [yN] "
read response

if [ "$response" = "y" ]
then
	file=$(echo "test/cases/$type/$expression" | sed 's/*/×/g')
	
	cp "$TEMPORARY_FILE" "$file"
	echo "$PREFIX created: $file"
else
	echo "$PREFIX not created"
fi

rm $TEMPORARY_FILE
