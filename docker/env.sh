#!/bin/bash

GCC_VERSION=13.2.0
BINUTILS_VERSION=2.41

TARGET=i386-elf
PREFIX=/kfs/cross-compiler
PATH=$PREFIX/bin:$PATH

THREADS=`nproc`

export TARGET
export PREFIX
export PATH
export THREADS

export GCC_VERSION
export BINUTILS_VERSION
