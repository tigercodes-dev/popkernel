#!/bin/bash

if [ ! -f dist/x86_64-popkernel.iso ]; then
    echo "You have to build the ISO before you can run it!"
fi

qemu-system-x86_64 -cdrom dist/x86_64-popkernel.iso
