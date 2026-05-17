# PopKernel

A operating system kernel that pops.

## Dependencies

- `make` - build system
- `nasm` - assembler
- `qemu-system-x86` - virtualization/testing
- `grub` - creating bootable ISO
- `xorriso` - needed by grub to create the ISO
- `kconfig-frontends` - used for the menuconfig
- Extra tools for cross compiling GCC and Binutils
    - gcc, g++, bison, flex, libgmp, libmpc, libmpfr, texinfo

### Ubuntu, Debian (apt)
```
$ sudo apt install make nasm qemu-system-x86 grub2-common grub-pc-bin xorriso build-essential bison flex libgmp-dev libmpc-dev libmpfr-dev texinfo kconfig-frontends
```

## Building

### Toolchain

Before you can build, you need the x86_64-elf cross compiler.
Run `scripts/build-toolchain.sh` to build it. This may take a while.

### Code

Firstly, configure your build. You can use `make defconfig` to load a default configuration, or you can use `make menuconfig` for more advanced configuration.
If you have already built the OS, you will need to run `make clean` to make sure all build files are removed.

Run `make` to build the kernel using the Makefile. A bootable ISO disk image will be output to the `dist` directory.

## Testing

Use `./run.sh` to boot the OS in QEMU.

## Copyright

*PopKernel OS*

*Copyright (C) 2026  tigercodes-dev*

*This program is free software: you can redistribute it and/or modify*
*it under the terms of the GNU General Public License as published by*
*the Free Software Foundation, either version 3 of the License, or*
*(at your option) any later version.*

*This program is distributed in the hope that it will be useful,*
*but WITHOUT ANY WARRANTY; without even the implied warranty of*
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the*
*GNU General Public License for more details.*

*You should have received a copy of the GNU General Public License*
*along with this program.  If not, see <https://www.gnu.org/licenses/>.*

See [COPYING](./COPYING) for more information.
