#    PopKernel OS Makefile
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

export ARCH ?= x86_64
export TARGET := $(ARCH)-elf

export BUILDDIR := $(abspath build)
export DISTDIR := $(abspath dist)
export MEDIADIR := $(abspath media)
export SCRIPTSDIR := $(abspath scripts)
export TOOLCHAINDIR := $(abspath toolchain)

export ISOROOT := $(MEDIADIR)/iso-$(ARCH)

export AS := nasm
export CC := $(TARGET)-gcc
export CXX := $(TARGET)-g++
export LD := $(TARGET)-ld

export ASFLAGS :=
export CFLAGS := -std=c99 -g
export CXXFLAGS := -g
export LDFLAGS :=
export LDLIBS := 

TEXTVIEWER ?= less

# Add the toolchain binaries to PATH
export PATH := $(TOOLCHAINDIR)/$(TARGET)/bin:$(PATH)

.PHONY: all all-x86_64 iso iso-x86_64 kernel kernel-x86_64 clean help license

all: all-$(ARCH)

all-x86_64: iso-x86_64

iso: iso-$(ARCH)

iso-x86_64: kernel-x86_64
	@echo "Copying boot files to iso..."
	cp $(DISTDIR)/x86_64-pkrnl.kb0.bin $(ISOROOT)/boot/pkrnl.kb0
	@echo "Creating bootable iso..."
	grub-mkrescue -o $(DISTDIR)/x86_64-popkernel.iso $(ISOROOT)
	@echo "$(DISTDIR)/x86_64-popkernel.iso is ready."

kernel: kernel-$(ARCH)

kernel-x86_64:
	@$(MAKE) -C src/kernel-x86_64

clean:
	rm -rf $(BUILDDIR)/{*,.*}
	rm -rf $(DISTDIR)/{*,.*}
	rm -f $(ISOROOT)/boot/pkrnl.kb*

help:
	@echo "PopKernel OS"
	@echo "Copyright (C) 2026  tigercodes-dev"
	@echo
	@echo "This program is free software: you can redistribute it and/or modify"
	@echo "it under the terms of the GNU General Public License as published by"
	@echo "the Free Software Foundation, either version 3 of the License, or"
	@echo "(at your option) any later version."
	@echo
	@echo "This program is distributed in the hope that it will be useful,"
	@echo "but WITHOUT ANY WARRANTY; without even the implied warranty of"
	@echo "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
	@echo "GNU General Public License for more details."
	@echo
	@echo "You should have received a copy of the GNU General Public License"
	@echo "along with this program.  If not, see <https://www.gnu.org/licenses/>."
	@echo
	@echo "-------------------------------------------------------------------------"
	@echo
	@echo "Makefile Targets:"
	@echo
	@echo "Build Targets:"
	@echo "  all: build everything for the configured architecture"
	@echo "  iso: build the ISO for the configured architecture"
	@echo "  kernel: build the kernel for the configured architecture"
	@echo
	@echo "Build (for architecture):"
	@echo "  all-x86_64: build everything for x86_64"
	@echo "  iso-x86_64: build the ISO for the x86_64"
	@echo "  kernel-x86_64: build the kernel for x86_64"
	@echo
	@echo "Clean Targets:"
	@echo "  clean: delete build files"
	@echo
	@echo "Help Targets:"
	@echo "  help: displays this help message"
	@echo "  license: show the license (viewer program can be changed by setting TEXTVIEWER)"
	@echo

license:
	@$(TEXTVIEWER) < COPYING
	@echo
