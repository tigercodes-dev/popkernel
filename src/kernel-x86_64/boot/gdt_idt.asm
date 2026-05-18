;    PopKernel OS - x86_64 GDT and IDT loader
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

bits 64

section .text

global GDT_load
GDT_load:
    cli

    lgdt [rdi]

    and rsi, 0xFFFF
    push rsi
    lea rax, [rel .cs_reloaded]
    push rax
    retfq

.cs_reloaded:
    mov ds, dx
    mov es, dx
    mov fs, dx
    mov gs, dx
    mov ss, dx

    ret
