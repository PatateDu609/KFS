#!/bin/bash

(return 0 2>/dev/null) && sourced=1 || sourced=0

source ./env.sh

if [ $sourced -eq 1 ]; then
	echo "Exporting cross-compiler environment variables..."
	export PATH
	export PREFIX
	export TARGET
	echo "Done."
	return 0
fi

function init {
  local PREFIX=$1

  mkdir -p "$PREFIX"/{src,bin,lib,include}
}

if [ "$1" = "init" ]; then
  init "$PREFIX"
fi

if [ "$1" = "gcc" ]; then
  source ./setup-gcc.sh
  install_gcc "$THREADS" "$TARGET" "$GCC_VERSION" "$PREFIX"
fi

if [ "$1" = "binutils" ]; then
  source ./setup-binutils.sh
  install_binutils "$THREADS" "$TARGET" "$BINUTILS_VERSION" "$PREFIX"
fi
