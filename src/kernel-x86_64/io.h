/*
    PopKernel OS - x86_64 kernel IO ports
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

#ifndef IO_H
#define IO_H

#include <integers.h>

// Output a byte (8 bits) to a IO port
void outb(u16 port, u8 data);

// Take a byte (8 bits) of input from a IO port
u8 inb(u16 port);

// Output a word (16 bits) to a IO port
void outw(u16 port, u16 data);

// Take a word (16 bits) of input from a IO port
u16 inw(u16 port);

// Output a long (32 bits) to a IO port
void outl(u16 port, u32 data);

// Take a long (32 bits) of input from a IO port
u32 inl(u16 port);

#endif
