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

SRC_C := $(shell find -type f -name '*.c')
OBJ_C := $(patsubst %.c, $(BUILDDIR)/kernel-x86_64/%.c.o, $(SRC_C))

LDFLAGS += -n
CFLAGS += -I ../include -ffreestanding

ifeq ($(CONFIG_MEMORY_MAP),y)
LDFLAGS += -Map=$(ROOTDIR)/$(CONFIG_MEMORY_MAP_OUTPUT)
endif

ASFLAGS += -dSTACKSIZE=$(CONFIG_STACK_SIZE)

LDFLAGS += --defsym _kernel_load=$(CONFIG_KERNEL_LOAD_ADDRESS)

ifeq ($(CONFIG_DEBUGGING),y)
CFLAGS += -DDEBUG_ENABLED
ifeq ($(CONFIG_DEBUG_E9_HACK),y)
CFLAGS += -DE9_DEBUG_ENABLED
endif
endif

.PHONY: all kernel-x86_64

all: kernel-x86_64

$(BUILDDIR)/kernel-x86_64/%.asm.o: %.asm
	@mkdir -p $(@D)
	@$(AS) $(ASFLAGS) -felf64 -o $@ $<
	@echo "  AS $< --> $@"

$(BUILDDIR)/kernel-x86_64/%.c.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "  CC $< --> $@"

kernel-x86_64: $(DISTDIR)/x86_64-pkrnl.kb0.bin

$(DISTDIR)/x86_64-pkrnl.kb0.bin: linker.ld $(OBJ_ASM) $(OBJ_C)
	@mkdir -p $(@D)
	@$(LD) $(LDLIBS) $(LDFLAGS) -T $< -o $@ $(OBJ_ASM) $(OBJ_C)
	@echo "  LD --> $@"
