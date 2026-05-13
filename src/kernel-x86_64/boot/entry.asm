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

section .entry

global start
start:
    mov word [0xB8000], 0x2F50
    mov word [0xB8002], 0x2F4B
    mov word [0xB8004], 0x2F52
    mov word [0xB8006], 0x2F4E
    mov word [0xB8008], 0x2F4C
    hlt

