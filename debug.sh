#!/bin/bash

if [ ! -f dist/x86_64-popkernel.iso ] || [ ! -f dist/x86_64-pkrnl.dbg ]; then
    echo "You have to build the ISO with debug symbols before you can run it!"
fi

echo "Run 'gdb dist/x86_64-pkrnl.dbg' and connect to QEMU with 'target remote :1234'"

qemu-system-x86_64 -s -S -cdrom dist/x86_64-popkernel.iso \
    -device isa-debugcon,iobase=0xe9,chardev=log -chardev stdio,id=log