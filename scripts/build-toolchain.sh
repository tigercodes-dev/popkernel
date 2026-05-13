#!/bin/bash

#    PopKernel OS Build Toolchain Script
#    Copyright (C) 2026  tigercodes-dev
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Builds the toolchain

set -e

# Configurations

TARGET=x86_64-elf
if [[ -n "$1" ]]; then TARGET="$1"; fi

GNU_WEBSITE="https://ftpmirror.gnu.org/"
BINUTILS_VERSION=2.46.0
GCC_VERSION=15.2.0

MAKE_OPTIONS="-j$(nproc)"
BINUTILS_OPTIONS="--with-sysroot --disable-nls --disable-werror"
GCC_OPTIONS="--disable-nls --enable-languages=c,c++ --without-headers"

# Toolchain Setup

TOOLCHAIN_DIR=$(realpath toolchain)
mkdir -p $TOOLCHAIN_DIR

TOOLCHAIN_TARGET=$TOOLCHAIN_DIR/$TARGET
mkdir -p $TOOLCHAIN_TARGET

pushd $TOOLCHAIN_DIR &> /dev/null

# Cross Binutils x86_64-elf

SECONDS=0

if [ ! -f "binutils-$BINUTILS_VERSION.tar.xz" ]; then
    wget "$GNU_WEBSITE/gnu/binutils/binutils-$BINUTILS_VERSION.tar.xz"
fi
tar -xf binutils-$BINUTILS_VERSION.tar.xz

# Set up build dir
mkdir -p binutils-build
pushd binutils-build &> /dev/null
rm -rf ./* ./.*

# Run configure
../binutils-$BINUTILS_VERSION/configure --prefix=$TOOLCHAIN_TARGET --target=$TARGET $BINUTILS_OPTIONS

# Build and install
make $MAKE_OPTIONS
make $MAKE_OPTIONS install

popd &> /dev/null

BINUTILS_TIME=$SECONDS

# Cross GCC x86_64-elf

SECONDS=0

if [ ! -f "gcc-$GCC_VERSION.tar.xz" ]; then
    wget "$GNU_WEBSITE/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.xz"
fi
tar -xf gcc-$GCC_VERSION.tar.xz

# Set up build dir
mkdir -p gcc-build
pushd gcc-build &> /dev/null
rm -rf ./* ./.*

# Run configure
../gcc-$GCC_VERSION/configure --prefix=$TOOLCHAIN_TARGET --target=$TARGET $GCC_OPTIONS

# Build and install
make $MAKE_OPTIONS all-gcc all-target-libgcc
make $MAKE_OPTIONS install-gcc install-target-libgcc

popd &> /dev/null

GCC_TIME=$SECONDS

echo -e "\e[32;1mToolchain finished building.\e[0m"
printf "binutils build time: %us\n" $BINUTILS_TIME
printf "gcc build time: %us\n" $GCC_TIME 
printf "total build time: %us\n" $(($BINUTILS_TIME + $GCC_TIME))

popd &> /dev/null
