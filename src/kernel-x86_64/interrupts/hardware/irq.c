/*
    PopKernel OS - x86_64 kernel interrupt request handlers
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

#define DEBUG_ENABLED 1

#include <stddef.h>
#include "irq.h"
#include "../../debugging/logging.h"

static int pic_remap_offset = 32;

static InterruptHandler handlers[16];

static const char* const irq_str[] = {
    "System Timer",
    "Keyboard",
    "IRQ Cascade",
    "COM2",
    "COM1",
    "LPT2",
    "Floppy Disk",
    "LPT1",
    "CMOS Real-Time Clock",
    "",
    "",
    "",
    "PS/2 Mouse",
    "Coprocessor",
    "Primary ATA Drive",
    "Secondary ATA Drive",
};

void IRQ_interrupt_handler(struct InterruptStack* stack) {
    int irq = stack->interrupt - pic_remap_offset;

    if (handlers[irq] != NULL) {
        handlers[irq](stack);
    } else {
        #if DEBUG_ENABLED
        debug_logf(LOG_WARN, "Unhandled hardware interrupt IRQ %u: %s\n", irq, irq_str[irq]);
        debug_logf(LOG_DEBUG, "IRR=0x%x ISR=0x%x\n", PIC_8259_get_IRR(), PIC_8259_get_ISR());
        #endif
    }

    PIC_8259_EOI(irq);
}

void IRQ_setup(int remap_offset) {
    pic_remap_offset = remap_offset;
    PIC_8259_setup(remap_offset);

    for (int i = 0; i < 16; i++) {
        ISR_set_handler(remap_offset + i, IRQ_interrupt_handler);
    }
}

void IRQ_set_handler(int irq, InterruptHandler handler) {
    handlers[irq] = handler;
}
