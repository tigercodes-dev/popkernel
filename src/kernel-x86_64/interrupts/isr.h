/*
    PopKernel OS - x86_64 kernel interrupt service routines
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

#ifndef INT_ISR_H
#define INT_ISR_H

#include <integers.h>

struct __attribute__((packed)) InterruptStack {
    u64 ds;
    u64 r15, r14, r13, r12, r11, r10, r9, r8;
    u64 rdi, rsi, rbp, _rsp, rbx, rdx, rcx, rax;
    u64 interrupt, err_code;
    u64 rip, cs, rflags, rsp, ss;
};

typedef void (*InterruptHandler)(struct InterruptStack* stack);

void ISR_setup_interrupts();

void ISR_set_handler(u8 interrupt, InterruptHandler handler);

#endif
