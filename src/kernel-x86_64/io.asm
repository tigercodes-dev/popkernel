;     PopKernel OS - x86_64 kernel IO ports
;     Copyright (C) 2026  tigercodes-dev
;
;     This program is free software: you can redistribute it and/or modify
;     it under the terms of the GNU General Public License as published by
;     the Free Software Foundation, either version 3 of the License, or
;     (at your option) any later version.
;
;     This program is distributed in the hope that it will be useful,
;     but WITHOUT ANY WARRANTY; without even the implied warranty of
;     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;     GNU General Public License for more details.
;
;     You should have received a copy of the GNU General Public License
;     along with this program.  If not, see <https://www.gnu.org/licenses/>.

bits 64

section .text

; void outb(u16 port, u8 data);
global outb
outb:
    mov rdx, rdi
    mov rax, rsi
    out dx, al
    ret

; u8 inb(u16 port);
global inb
inb:
    xor rax, rax
    mov rdx, rdi
    in al, dx
    ret

; void outw(u16 port, u16 data);
global outw
outw:
    mov rdx, rdi
    mov rax, rsi
    out dx, ax
    ret

; u16 inw(u16 port);
global inw
inw:
    xor rax, rax
    mov rdx, rdi
    in ax, dx
    ret

; void outl(u16 port, u32 data);
global outl
outl:
    mov rdx, rdi
    mov rax, rsi
    out dx, eax
    ret

; u32 inl(u16 port);
global inl
inl:
    xor rax, rax
    mov rdx, rdi
    in eax, dx
    ret
