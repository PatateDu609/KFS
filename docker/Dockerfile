FROM debian:bookworm
LABEL authors="teyber"

ENV DEBIAN_FRONTEND="noninteractive"

RUN mkdir -p /kfs
WORKDIR /kfs

RUN apt update && apt upgrade -y
RUN apt install  \
    build-essential  \
    xorriso  \
    nasm  \
    grub-pc-bin  \
    cmake  \
    gdb  \
    gcc \
    g++ \
    clang \
    make \
    ninja-build \
    cmake \
    autoconf \
    automake \
    libtool \
    valgrind \
    locales-all \
    dos2unix \
    rsync \
    tar \
    python3 \
    python3-dev \
    bash  \
    libmpc-dev \
    libgmp3-dev \
    libmpfr-dev \
    texinfo \
    bison \
    flex \
    libisl-dev \
    wget \
    -y
RUN apt clean

RUN mkdir -p docker
COPY docker/env.sh ./docker/
COPY docker/setup.sh ./docker/
RUN chmod u+x docker/*.sh

RUN cd ./docker && ./setup.sh init

COPY docker/setup-binutils.sh ./docker/
RUN cd ./docker && ./setup.sh binutils

COPY docker/setup-gcc.sh ./docker/
RUN cd ./docker && ./setup.sh gcc

LABEL org.opencontainers.image.source=https://github.com/PatateDu609/KFS
