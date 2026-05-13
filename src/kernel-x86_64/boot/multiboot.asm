;    PopKernel OS - x86_64 kernel multiboot header
;    Copyright (C) 2026  tigercodes-dev
;
;    This program is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation, either version 3 of the License, or
;    (at your option) any later version.
;
;    This program is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with this program.  If not, see <https://www.gnu.org/licenses/>.

section .multiboot

multiboot_start:

    dd 0xe85250d6 ; multiboot2 magic number
    dd 0
    dd multiboot_end - multiboot_start
    dd 0x100000000 - (0xe85250d6 + 0 + (multiboot_end - multiboot_start))

    dw 0
    dw 0
    dd 8

multiboot_end:
