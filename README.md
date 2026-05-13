# PopKernel

A operating system kernel that pops.

## Dependencies

- `make` - build system
- `nasm` - assembler
- `qemu-system-x86` - virtualization/testing
- `grub` - creating bootable ISO
- `xorriso` - needed by grub to create the ISO
- Extra tools for cross compiling GCC and Binutils
    - gcc, g++, bison, flex, libgmp, libmpc, libmpfr, texinfo

### Ubuntu, Debian (apt)
```
$ sudo apt install make nasm qemu-system-x86 grub2-common grub-pc-bin xorriso build-essential bison flex libgmp-dev libmpc-dev libmpfr-dev texinfo
```

## Building

### Toolchain

Before you can build, you need the x86_64-elf cross compiler.
Run `scripts/build-toolchain.sh` to build it. This may take a while.

### Code

Run `make` to build the kernel using the Makefile. A bootable ISO disk image will be output to the `dist` directory.

## Testing

Use `./run.sh` to boot the OS in QEMU.
