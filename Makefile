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

# Add the toolchain binaries to PATH
export PATH := $(TOOLCHAINDIR)/$(TARGET)/bin:$(PATH)

.PHONY: all all-x86_64 iso iso-x86_64 kernel kernel-x86_64

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
