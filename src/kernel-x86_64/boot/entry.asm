;    PopKernel OS - x86_64 kernel entry point
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

bits 32

; define the stack size
%ifndef STACKSIZE
%define STACKSIZE 8192
%endif
 
section .entry

extern setup64

global start
start:
    mov esp, stack_top

    call multiboot_test
    call cpuid_test
    call longmode_test

    call setup_paging

    lgdt [gdt64_desc]
    jmp gdt64.code_seg:setup64

    jmp fail ; this shouldnt ever happen but just in case

multiboot_test:
    cmp eax, 0x36d76289
    jne fail
    ret

cpuid_test:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx

    je fail
    ret

longmode_test:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000000
    jbe fail

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz fail
    ret

setup_paging:
    mov eax, lvl3_pg_table
    or eax, 0x3 ; set present and writable
    mov [lvl4_pg_table], eax

    mov eax, lvl2_pg_table
    or eax, 0x3 ; set present and writable
    mov [lvl3_pg_table], eax

    mov ecx, 0

.map_loop:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011
    mov [lvl2_pg_table + ecx * 8], eax

    inc ecx
    cmp ecx, 512
    jne .map_loop


    mov eax, lvl4_pg_table
    mov cr3, eax

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax
    ret

fail:
    mov word [0xB8000], 0x1F45
    mov word [0xB8002], 0x1F52
    mov word [0xB8004], 0x1F52
    mov word [0xB8006], 0x1F4F
    mov word [0xB8008], 0x1F52
    hlt

section .bss

align 4096
lvl4_pg_table: resb 4096
lvl3_pg_table: resb 4096
lvl2_pg_table: resb 4096

resb STACKSIZE
stack_top:

section .rodata

gdt64:
    dq 0 ; Null

.code_seg: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) ; Code segment

gdt64_desc:
    dw $ - gdt64 - 1
    dq gdt64
