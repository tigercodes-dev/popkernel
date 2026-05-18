#!/bin/bash

if [ ! -f dist/x86_64-popkernel.iso ]; then
    echo "You have to build the ISO before you can run it!"
fi

qemu-system-x86_64 -drive file=dist/x86_64-popkernel.iso,media=cdrom,if=ide \
    -device isa-debugcon,iobase=0xe9,chardev=log -chardev stdio,id=log
