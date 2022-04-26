COMPILED_DIRECTORY=compiled

cd test/

rm -rf $COMPILED_DIRECTORY
mkdir $COMPILED_DIRECTORY

for file in *.cpp; do
	target=$(basename $file .cpp)
	
	echo Compiling $file
	
	g++ $file -o $COMPILED_DIRECTORY/$file-x64.out -std=c++98
	g++ $file -o $COMPILED_DIRECTORY/$file-x64.o   -std=c++98
	g++ $file -o $COMPILED_DIRECTORY/$file-x64.so  -std=c++98     -shared -fPIC
	g++ $file -o $COMPILED_DIRECTORY/$file-x32.out -std=c++98 -m32
	g++ $file -o $COMPILED_DIRECTORY/$file-x32.o   -std=c++98 -m32
	g++ $file -o $COMPILED_DIRECTORY/$file-x32.so  -std=c++98 -m32 -shared -fPIC
done


for file in *.c; do
	target=$(basename $file .c)
	
	echo Compiling $file
	
	gcc $file -o $COMPILED_DIRECTORY/$file-x64.out
	gcc $file -o $COMPILED_DIRECTORY/$file-x64.o
	gcc $file -o $COMPILED_DIRECTORY/$file-x64.so       -shared -fPIC
	gcc $file -o $COMPILED_DIRECTORY/$file-x32.out -m32
	gcc $file -o $COMPILED_DIRECTORY/$file-x32.o   -m32
	gcc $file -o $COMPILED_DIRECTORY/$file-x32.so  -m32 -shared -fPIC
done
