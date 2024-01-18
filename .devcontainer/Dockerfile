FROM --platform=linux/arm64 debian:bullseye-slim

# basic
RUN apt-get update \
    && apt-get install -y file curl vim

# c/c++
RUN apt-get update \
    && apt-get install -y build-essential \
        gcc \
        g++ \
        gdb \
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
        python \
        python-dev \
        git \
        strace \
    && apt-get clean