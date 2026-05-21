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

#include "idt.h"
#include "isr.h"
#include <stddef.h>
#include "../debugging/logging.h"
#include "../drivers/graphics/vga/textmode.h"
#include "../panic.h"

static InterruptHandler handlers[256] = {NULL};

static const char* const exception_str[] = {
    "Divison Error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "",
};

void IDT_setup_entries();

void ISR_setup_interrupts() {
    IDT_setup_entries();
    for (int i = 0; i < 256; i++) {
        IDT_enable_gate(i);
    }
}

void ISR_C_handler(struct InterruptStack* stack) {
    if (handlers[stack->interrupt] != NULL) {
        handlers[stack->interrupt](stack);
    } else if (stack->interrupt < 32) {
        #if DEBUG_ENABLED
        debug_logf(LOG_ERROR, "Unhandled CPU Exception 0x%x: %s\n", stack->interrupt, exception_str[stack->interrupt]);
        // Show Register Values
        debug_logf(LOG_DEBUG, "rax=0x%x rcx=0x%x rdx=0x%x rbx=0x%x rsp=0x%x rbp=0x%x rsi=0x%x rdi=0x%x\n",
            stack->rax, stack->rcx, stack->rdx, stack->rbx, stack->rsp, stack->rbp, stack->rsi, stack->rdi);
        debug_logf(LOG_DEBUG, "r8=0x%x r9=0x%x r10=0x%x r11=0x%x r12=0x%x r13=0x%x r14=0x%x r15=0x%x\n",
            stack->r8, stack->r9, stack->r10, stack->r11, stack->r12, stack->r13, stack->r14, stack->r15);
        debug_logf(LOG_DEBUG, "cs=0x%x ds=0x%x ss=0x%x rip=0x%x rflags=0x%x err_code=0x%x\n",
            stack->cs, stack->ds, stack->ss, stack->rip, stack->rflags, stack->err_code);
        #endif
        kernel_panic("Unhandled CPU Exception Occurred");
    }
}

void ISR_set_handler(u8 interrupt, InterruptHandler handler) {
    handlers[interrupt] = handler;
    IDT_enable_gate(interrupt);
}
