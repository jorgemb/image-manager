FROM ubuntu:latest

ENV VCPKG_ROOT=/vcpkg
RUN apt-get update && apt-get install -y \
    build-essential \
    bison \
    cmake \
    clang \
    git \
    gdb \
    libgtk-3-dev  \
    libgstreamer-plugins-base1.0-dev \
    ninja-build \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 https://github.com/microsoft/vcpkg.git $VCPKG_ROOT

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

WORKDIR /app/

COPY . .
