/*
    PopKernel OS - x86_64 kernel ATA PIO mode
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

#include "pio.h"
#include "../../io.h"
#include "../../interrupts/hardware/irq.h"

#define CMD_IDENTIFY 0xEC
#define CMD_IDENTIFY_PACKET 0xA1

#define BSY_BIT 0x80
#define DRQ_BIT 0x08
#define ERR_BIT 0x01

static void iowait(ATADevice* device) {
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
}

static bool ready1 = false;
static bool ready2 = false;

void ATA_primary_irq(struct InterruptStack* stack) {
    ready1 = true;
    inb(0x1F7);
}

void ATA_secondary_irq(struct InterruptStack* stack) {
    ready2 = true;
    inb(0x177);
}

void ATA_setup_irqs() {
    IRQ_set_handler(14, ATA_primary_irq);
    IRQ_set_handler(15, ATA_secondary_irq);
}

void ATA_software_reset(ATADevice* device) {
    outb(device->dev_ctrl_reg, 0x04); // Software reset bit
    iowait(device);
    outb(device->dev_ctrl_reg, 0);
}

static bool wait_irq(ATADevice* device) {
    int counter = 0;
    if (device->bus == 1) {
        while (!ready1) {
            if (++counter >= 1000000) {
                if (inb(device->status_reg) & 0x01 != 0) return false;
            }
        }
        ready1 = false;
    } else {
        while (!ready2) {
            if (++counter >= 1000000) {
                if (inb(device->status_reg) & 0x01 != 0) return false;
            }
        }
        ready2 = false;
    }
    return true;
}

void ATA_identify_device(ATADevice* device) {
    ATA_software_reset(device);
    
    if (!wait_irq(device)) {
        device->status = 4;
        return;
    }

    if (inb(device->lba_mid_reg) == 0x00 && inb(device->lba_high_reg) == 0x00) {
        device->packet = false;
        device->sata = false;
    } else if (inb(device->lba_mid_reg) == 0x14 && inb(device->lba_high_reg) == 0xEB) {
        device->packet = true;
        device->sata = false;
    } else if (inb(device->lba_mid_reg) == 0x3C && inb(device->lba_high_reg) == 0xC3) {
        device->packet = false;
        device->sata = true;
    } else {
        device->status = 1;
        return;
    }

    if (device->sata) {
        device->status = 1;
        return;
    } else {
        outb(device->drive_head_reg, 0xA0 | (device->slave << 4));
        outb(device->sector_count_reg, 0);
        outb(device->lba_low_reg, 0);
        outb(device->lba_mid_reg, 0);
        outb(device->lba_high_reg, 0);
        iowait(device);

        outb(device->command_reg, device->packet ? CMD_IDENTIFY_PACKET : CMD_IDENTIFY);
        if (inb(device->status_reg) == 0) {
            device->status = 2;
            return;
        }

        if (inb(device->lba_low_reg) != 0 | inb(device->lba_high_reg) != 0) {
            device->status = 3;
            return;
        }

        if (!wait_irq(device)) {
            device->status = 4;
            return;
        }

        for (int i = 0; i < 256; i++) {
            device->buffer[i] = inw(device->data_reg);
        }

        device->status = 0;
    }
}
