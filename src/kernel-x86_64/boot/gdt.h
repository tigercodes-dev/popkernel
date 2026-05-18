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

#include <integers.h>

struct __attribute__((packed)) GDTEntry {
    u16 limit_low;
    u16 base_low;
    u8 base_mid;
    u8 access;
    u8 limit_high_flags;
    u8 base_high;
};

struct __attribute__((packed)) GDTDescriptor {
    u16 size;
    struct GDTEntry* gdt;
};

void GDT_setup();
