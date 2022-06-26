rm -rf binaries
mkdir binaries

for file in sources/*.cpp; do
	file=$(basename $file)

	echo Compiling $file
	
	g++ sources/$file -o binaries/$file-x64.out -std=c++98
	g++ sources/$file -o binaries/$file-x64.o   -std=c++98
	g++ sources/$file -o binaries/$file-x64.so  -std=c++98     -shared -fPIC
	g++ sources/$file -o binaries/$file-x32.out -std=c++98 -m32
	g++ sources/$file -o binaries/$file-x32.o   -std=c++98 -m32
	g++ sources/$file -o binaries/$file-x32.so  -std=c++98 -m32 -shared -fPIC
done


for file in sources/*.c; do
	file=$(basename $file)
	
	echo Compiling $file
	
	gcc sources/$file -o binaries/$file-x64.out
	gcc sources/$file -o binaries/$file-x64.o
	gcc sources/$file -o binaries/$file-x64.so       -shared -fPIC
	gcc sources/$file -o binaries/$file-x32.out -m32
	gcc sources/$file -o binaries/$file-x32.o   -m32
	gcc sources/$file -o binaries/$file-x32.so  -m32 -shared -fPIC
done
