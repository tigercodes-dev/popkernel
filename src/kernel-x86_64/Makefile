#    PopKernel OS kernel-x86_64 Makefile
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

SRC_ASM := $(shell find -type f -name '*.asm')
OBJ_ASM := $(patsubst %.asm, $(BUILDDIR)/kernel-x86_64/%.asm.o, $(SRC_ASM))

ASFLAGS += -felf64
LDFLAGS += -n

.PHONY: all kernel-x86_64

all: kernel-x86_64

$(BUILDDIR)/kernel-x86_64/%.asm.o: %.asm
	@mkdir -p $(@D)
	@$(AS) $(ASFLAGS) -o $@ $<
	@echo "AS $< --> $@"

kernel-x86_64: $(DISTDIR)/x86_64-pkrnl.kb0.bin

$(DISTDIR)/x86_64-pkrnl.kb0.bin: $(OBJ_ASM)
	@mkdir -p $(@D)
	@$(LD) $(LDLIBS) $(LDFLAGS) -T linker.ld -o $@ $^
	@echo "LD --> $@"
