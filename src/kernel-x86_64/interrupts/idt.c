/*
    PopKernel OS - x86_64 interrupt descriptor table
    Copyright (C) 2026  tigercodes-dev

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "idt.h"
#include <binary.h>

void IDT_load(struct IDTDescriptor* descriptor);

static struct IDTEntry idt[256];

static struct IDTDescriptor idt_desc = { sizeof(idt) - 1, idt };

void IDT_set_gate(u8 interrupt, void* offset, u16 segment_selector, u8 flags) {
    struct IDTEntry* entry = &idt[interrupt];
    entry->offset_low = ((u64)offset) & 0xFFFF;
    entry->segment_selector = segment_selector;
    entry->ist = 0; // We dont have an IST or TSS yet
    entry->flags = flags;
    entry->offset_mid = (((u64)offset) >> 16) & 0xFFFF;
    entry->offset_high = (((u64)offset) >> 32) & 0xFFFFFFFF;
    entry->_reserved = 0;
}

void IDT_enable_gate(u8 interrupt) {
    SET_FLAG(idt[interrupt].flags, IDT_PRESENT);
}

void IDT_disable_gate(u8 interrupt) {
    UNSET_FLAG(idt[interrupt].flags, IDT_PRESENT);
}

void IDT_setup() {
    IDT_load(&idt_desc);
}
