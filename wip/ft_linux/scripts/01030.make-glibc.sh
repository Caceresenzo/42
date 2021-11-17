base=$(pwd)

pushd $LFS/sources
	. $base/$(dirname $0)/helper/untar.sh glibc

	pushd $name
		case $(uname -m) in
			i?86)
				ln -sfv ld-linux.so.2 $LFS/lib/ld-lsb.so.3
			;;

			x86_64)
				ln -sfv ../lib/ld-linux-x86-64.so.2 $LFS/lib64
				ln -sfv ../lib/ld-linux-x86-64.so.2 $LFS/lib64/ld-lsb-x86-64.so.3
			;;
		esac

		patch -Np1 -i ../glibc-*.patch || true

		rm -rf build
		mkdir -vp build

		pushd build
			echo "rootsbindir=/usr/sbin" > configparms

			../configure                             \
				--prefix=/usr                      \
				--host=$LFS_TGT                    \
				--build=$(../scripts/config.guess) \
				--enable-kernel=3.2                \
				--with-headers=$LFS/usr/include    \
				libc_cv_slibdir=/usr/lib

			make

			make DESTDIR=$LFS install

			sed '/RTLDLIST=/s@/usr@@g' -i $LFS/usr/bin/ldd

			echo 'int main(){}' > dummy.c
			$LFS_TGT-gcc dummy.c
			readelf -l a.out | grep '/ld-linux'
			rm -v dummy.c a.out

			$LFS/tools/libexec/gcc/$LFS_TGT/11.2.0/install-tools/mkheaders
		popd
	popd
popd
