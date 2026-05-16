/*
    PopKernel OS - x86_64 kernel E9 port hack loggging
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

#include "e9.h"
#include "../io.h"

void e9putc(char c) {
    outb(0xE9, c);
}

void e9puts(const char* s) {
    while (*s) {
        e9putc(*s);
        s++;
    }
}
