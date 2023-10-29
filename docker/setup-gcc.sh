#!/bin/bash

function install_gcc {
  local THREADS=$1
  local TARGET=$2
  local GCC_VERSION=$3
  local PREFIX=$4

  wget "https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz" -O "$PREFIX/src/gcc-$GCC_VERSION.tar.xz"
  cd "$PREFIX/src" || exit 1

  tar -xvf "gcc-$GCC_VERSION.tar.xz"
  rm "gcc-$GCC_VERSION.tar.xz"

  which -- "$TARGET-as" || echo "$TARGET-as" is not in the PATH

  mkdir -p build-gcc
  cd build-gcc || exit 1
  ../"gcc-$GCC_VERSION"/configure --target="$TARGET" --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
  make -j"$THREADS" all-gcc
  make -j"$THREADS" all-target-libgcc
  make install-gcc
  make install-target-libgcc
}
