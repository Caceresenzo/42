COMPILED_DIRECTORY=compiled

cd test/

rm -rf $COMPILED_DIRECTORY
mkdir $COMPILED_DIRECTORY

for file in *.cpp; do
	target=$(basename $file .cpp)
	
	g++ $file -o $COMPILED_DIRECTORY/$file-x64.out    
	g++ $file -o $COMPILED_DIRECTORY/$file-x64.o
	g++ $file -o $COMPILED_DIRECTORY/$file-x64.so       -shared -fPIC
	g++ $file -o $COMPILED_DIRECTORY/$file-x32.out -m32
	g++ $file -o $COMPILED_DIRECTORY/$file-x32.o   -m32
	g++ $file -o $COMPILED_DIRECTORY/$file-x32.so  -m32 -shared -fPIC
done


for file in *.c; do
	target=$(basename $file .c)
	
	gcc $file -o $COMPILED_DIRECTORY/$file-x64.out
	gcc $file -o $COMPILED_DIRECTORY/$file-x64.o
	gcc $file -o $COMPILED_DIRECTORY/$file-x64.so       -shared -fPIC
	gcc $file -o $COMPILED_DIRECTORY/$file-x32.out -m32
	gcc $file -o $COMPILED_DIRECTORY/$file-x32.o   -m32
	gcc $file -o $COMPILED_DIRECTORY/$file-x32.so  -m32 -shared -fPIC
done
