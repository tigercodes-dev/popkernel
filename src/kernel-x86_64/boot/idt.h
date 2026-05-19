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

#ifndef IDT_H
#define IDT_H

#include <integers.h>

struct __attribute__((packed)) IDTEntry {
    u16 offset_low;
    u16 segment_selector;
    u8 ist;
    u8 flags;
    u16 offset_mid;
    u32 offset_high;
    u32 _reserved;
};

struct __attribute__((packed)) IDTDescriptor {
    u16 size;
    struct IDTEntry* gdt;
};

void IDT_setup();

#endif
