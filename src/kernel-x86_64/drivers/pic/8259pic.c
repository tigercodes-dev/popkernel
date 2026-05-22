/*
    PopKernel OS - x86_64 kernel 8259 PIC driver
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

#include <binary.h>
#include "8259pic.h"
#include "../../io.h"

#define MASTER_PIC_CMD_PORT 0x20
#define MASTER_PIC_DAT_PORT 0x21
#define SLAVE_PIC_CMD_PORT 0xA0
#define SLAVE_PIC_DAT_PORT 0xA1

#define CASCADE_IRQ 2

#define PIC_EOI_CMD 0x20
#define PIC_READ_ISR_CMD 0x0A
#define PIC_READ_IRR_CMD 0x0B

enum ICW1 {
    ICW1_ICW4      = 0x01,
    ICW1_SINGLE    = 0x02,
    ICW1_INTERVAL4 = 0x04,
    ICW1_LEVEL     = 0x08,
    ICW1_INIT      = 0x10,
};

enum ICW4 {
    ICW4_8086 = 0x01,
    ICW4_AUTO = 0x02,
    ICW4_BUF_SLAVE = 0x08,
    ICW4_BUF_MASTER = 0x0C,
    ICW4_SFNM = 0x10
};

#define iowait() outb(0x80, 0);

void PIC_8259_enable() {
    outb(MASTER_PIC_DAT_PORT, 0);
    outb(SLAVE_PIC_DAT_PORT, 0);
}

void PIC_8259_disable() {
    outb(MASTER_PIC_DAT_PORT, 0xFF);
    outb(SLAVE_PIC_DAT_PORT, 0xFF);
}

void PIC_8259_mask(int irq) {
    if (irq < 8) {
        u8 master_mask = inb(MASTER_PIC_DAT_PORT);
        SET_FLAG(master_mask, 1 << irq);
        outb(MASTER_PIC_DAT_PORT, master_mask);
    } else {
        u8 slave_mask = inb(SLAVE_PIC_DAT_PORT);
        SET_FLAG(slave_mask, 1 << (irq - 8));
        outb(SLAVE_PIC_DAT_PORT, slave_mask);
    }
}

void PIC_8259_unmask(int irq) {
    if (irq < 8) {
        u8 master_mask = inb(MASTER_PIC_DAT_PORT);
        UNSET_FLAG(master_mask, 1 << irq);
        outb(MASTER_PIC_DAT_PORT, master_mask);
    } else {
        u8 slave_mask = inb(SLAVE_PIC_DAT_PORT);
        UNSET_FLAG(slave_mask, 1 << (irq - 8));
        outb(SLAVE_PIC_DAT_PORT, slave_mask);
    }
}

void PIC_8259_setup(int remap_offset) {
    outb(MASTER_PIC_CMD_PORT, ICW1_INIT | ICW1_ICW4);
    iowait();
    outb(SLAVE_PIC_CMD_PORT, ICW1_INIT | ICW1_ICW4);
    iowait();

    outb(MASTER_PIC_DAT_PORT, remap_offset);
    iowait();
    outb(SLAVE_PIC_DAT_PORT, remap_offset + 8);
    iowait();

    outb(MASTER_PIC_DAT_PORT, 1 << CASCADE_IRQ);
    iowait();
    outb(SLAVE_PIC_DAT_PORT, 2);
    iowait();

    outb(MASTER_PIC_DAT_PORT, ICW4_8086);
    iowait();
    outb(SLAVE_PIC_DAT_PORT, ICW4_8086);
    iowait();

    PIC_8259_enable();
}

void PIC_8259_EOI(int irq) {
    if (irq >= 8) {
        outb(SLAVE_PIC_CMD_PORT, PIC_EOI_CMD);
    }
    outb(MASTER_PIC_CMD_PORT, PIC_EOI_CMD);
}

u16 PIC_8259_get_IRR() {
    outb(MASTER_PIC_CMD_PORT, PIC_READ_IRR_CMD);
    outb(SLAVE_PIC_CMD_PORT, PIC_READ_IRR_CMD);
    return inb(MASTER_PIC_CMD_PORT) | (inb(SLAVE_PIC_CMD_PORT) << 8);
}

u16 PIC_8259_get_ISR() {
    outb(MASTER_PIC_CMD_PORT, PIC_READ_ISR_CMD);
    outb(SLAVE_PIC_CMD_PORT, PIC_READ_ISR_CMD);
    return inb(MASTER_PIC_CMD_PORT) | (inb(SLAVE_PIC_CMD_PORT) << 8);
}
