#!/bin/bash

error() {
    echo -e "\e[31;1m[ERROR]:\e[0m $1" >&2
    exit 1
}

warn() {
    echo -e "\e[33;1m[WARNING]:\e[0m $1" >&2
}

# Check Make

type -p make > /dev/null || error "Dependency: Make not found."
echo "Make: OK"

# Check NASM

type -p nasm > /dev/null || error "Dependency: NASM not found."
echo "NASM: OK"

# Check QEMU

type -p qemu-system-x86_64 > /dev/null || warn "Dependency: QEMU not found. You need it to test the OS."
echo "QEMU: OK"

# Check GRUB

type -p grub-mkrescue > /dev/null || error "Dependency: GRUB not found."
echo "GRUB: OK"

# Check xorriso

type -p xorriso > /dev/null || error "Dependency: xorriso (used by GRUB) not found."
echo "xorriso: OK"

# Check GCC

type -p gcc > /dev/null || error "Cross Compiler Dependency: GCC not found."

# Test if GCC works
echo "int main() { return 53; }" | gcc -x c - -o /tmp/gcctest || error "Cross Compiler Dependency: GCC does not work."
/tmp/gcctest; (($? == 53)) || error "Cross Compiler Dependency: GCC does not work."
rm -f /tmp/gcctest

echo "GCC: OK"

# Check g++
type -p g++ > /dev/null || error "Cross Compiler Dependency: GCC C++ not found."

# Test if g++ works
echo "int main() { return 107; }" | gcc -x c - -o /tmp/g++test || error "Cross Compiler Dependency: GCC C++ does not work."
/tmp/g++test ; (($? == 107)) || error "Cross Compiler Dependency: GCC C++ does not work."
rm -f /tmp/g++test

echo "GCC C++: OK"

# Check bison
type -p bison > /dev/null || error "Cross Compiler Dependency: bison not found."
echo "bison: OK"

# Check flex
type -p flex > /dev/null || error "Cross Compiler Dependency: flex not found."
echo "flex: OK"

# Check libgmp
ldconfig -p | grep 'libgmp\.so' > /dev/null || error "Cross Compiler Dependency: libgmp not found"
echo "libgmp: OK"

# Check libmpc
ldconfig -p | grep 'libmpc\.so' > /dev/null || error "Cross Compiler Dependency: libmpc not found"
echo "libmpc: OK"

# Check libmpfr
ldconfig -p | grep 'libmpfr\.so' > /dev/null || error "Cross Compiler Dependency: libmfr not found"
echo "libmpfr: OK"

# Check texinfo
type -p texi2any > /dev/null || error "Cross Compiler Dependency: texinfo not found."
echo "texinfo: OK"

# Check kconfig-frontends
type -p kconfig-mconf > /dev/null || error "Dependency: kconfig-frontends not found."
echo "kconfig-frontends: OK"

echo -e "\n\e[32;1m*All dependencies were found and are working.*\e[0m\n"