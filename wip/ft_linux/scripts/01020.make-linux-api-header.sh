base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh linux

	pushd $name
		make mrproper

		make headers
		find usr/include -name '.*' -delete
		rm usr/include/Makefile
		cp -rv usr/include $LFS/usr
	popd
popd
