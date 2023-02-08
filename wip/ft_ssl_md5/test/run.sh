command=$1

for f in test/case/*;
do
	bash test/one.sh $command $f
done
