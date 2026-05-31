#!/bin/bash

# Used by the Makefile to log commands during the build process

printf "  %-8s %s --> %s\n" "${1^^}" "$(realpath --relative-to=$ROOTDIR "$2")" "$(realpath --relative-to=$ROOTDIR "$3")"
