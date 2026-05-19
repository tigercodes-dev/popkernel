/*
    PopKernel OS - x86_64 global descriptor table
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

#include "gdt.h"

void GDT_load(struct GDTDescriptor* descriptor, u16 cs_new, u16 ds_new);

enum GDTAccess {
    GDT_ACCESSED = 0x01,

    GDT_CS_READABLE   = 0x02,
    GDT_DS_WRITEABLE  = 0x02,

    GDT_CS_CONFORMING = 0x04,
    GDT_DS_REVERSED   = 0x04,

    GDT_DATA_SEGMENT  = 0x10,
    GDT_CODE_SEGMENT  = 0x18,
    GDT_SYS_SEGMENT   = 0x00,
    
    GDT_RING_0        = 0x00,
    GDT_RING_1        = 0x20,
    GDT_RING_2        = 0x40,
    GDT_RING_3        = 0x60,

    GDT_PRESENT       = 0x80,
};

enum GDTFlags {
    GDT_64BITS        = 0x20,
    GDT_32BITS        = 0x40,
    GDT_16BITS        = 0x00,

    GDT_GRAN_1B       = 0x00,
    GDT_GRAN_4K       = 0x80,
};

static struct GDTEntry gdt[] = {
    { 0, 0, 0, 0, 0, 0 }, // NULL Descriptor
    {
        0xFFFF, 0, 0, GDT_CS_READABLE | GDT_CODE_SEGMENT | GDT_RING_0 | GDT_PRESENT,
        0xF | GDT_64BITS | GDT_GRAN_4K, 0
    }, // Kernel Mode Code Segment
    {
        0xFFFF, 0, 0, GDT_DS_WRITEABLE | GDT_DATA_SEGMENT | GDT_RING_0 | GDT_PRESENT,
        0xF | GDT_32BITS | GDT_GRAN_4K, 0
    }, // Kernel Mode Data Segment
    {
        0xFFFF, 0, 0, GDT_DS_WRITEABLE | GDT_DATA_SEGMENT | GDT_RING_3 | GDT_PRESENT,
        0xF | GDT_32BITS | GDT_GRAN_4K, 0
    }, // User Mode Data Segment
    {
        0xFFFF, 0, 0, GDT_CS_READABLE | GDT_CODE_SEGMENT | GDT_RING_3 | GDT_PRESENT,
        0xF | GDT_64BITS | GDT_GRAN_4K, 0
    }, // User Mode Code Segment
};

static struct GDTDescriptor gdt_desc = { sizeof(gdt) - 1, gdt };

void GDT_setup() {
    GDT_load(&gdt_desc, 0x08, 0x10);
}
