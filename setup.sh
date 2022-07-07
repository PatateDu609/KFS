#!/bin/bash

TARGET=i386-elf
PREFIX=$(pwd)/cross-compiler
PATH=$PREFIX/bin:$PATH

if [ $# -eq 0 ]; then
	echo "Exporting cross-compiler environment variables..."
	export PATH
	export PREFIX
	export TARGET
	echo "Done."
	return 0
fi

THREADS=`nproc`

rm -rf $PREFIX
mkdir -p $PREFIX/{src,bin,lib,include}

wget http://ftp.gnu.org/gnu/binutils/binutils-2.38.tar.xz -O $PREFIX/src/binutils-2.38.tar.xz
cd $PREFIX/src

tar -xvf binutils-2.38.tar.xz
rm binutils-2.38.tar.xz

mkdir -p build-binutils
cd build-binutils
../binutils-2.38/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
make -j$THREADS
make install

rm -rf build-binutils

wget https://ftp.gnu.org/gnu/gcc/gcc-12.1.0/gcc-12.1.0.tar.xz -O $PREFIX/src/gcc-12.1.0.tar.xz
cd $PREFIX/src

tar -xvf gcc-12.1.0.tar.xz
rm gcc-12.1.0.tar.xz

which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir -p build-gcc
cd build-gcc
../gcc-12.1.0/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers
make -j$THREADS all-gcc
make -j$THREADS all-target-libgcc
make install-gcc
make install-target-libgcc
