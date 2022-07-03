PROJECT=$1
URL=$2

TMP_DIR=$(echo /tmp/$PROJECT/)

rm -rf $TMP_DIR
mkdir -p $TMP_DIR

cd $TMP_DIR

wget $URL
tar -xvf *.tar.*

cd $PROJECT*/

if /bin/ls ./configure >/dev/null 2>&1;
then
	./configure
fi

make
