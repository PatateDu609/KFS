#!/bin/bash

function install_binutils {
  local THREADS=$1
  local TARGET=$2
  local BINUTILS_VERSION=$3
  local PREFIX=$4

  wget "http://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.xz" -O "$PREFIX/src/binutils-$BINUTILS_VERSION.tar.xz"
  cd "$PREFIX/src" || exit 1

  tar -xvf "binutils-$BINUTILS_VERSION.tar.xz"
  rm "binutils-$BINUTILS_VERSION.tar.xz"

  mkdir -p build-binutils
  cd build-binutils || exit 1
  ../"binutils-$BINUTILS_VERSION"/configure --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
  make -j"$THREADS"
  make install

  rm -rf build-binutils
}
