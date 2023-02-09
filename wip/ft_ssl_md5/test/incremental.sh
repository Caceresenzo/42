command=$1

mkdir -p /tmp/n/

for n in $(seq 1 1000); do
	head -c $n /dev/random > /tmp/n/$n
	bash test/one.sh $command /tmp/n/$n
done

rm -rf /tmp/n/
