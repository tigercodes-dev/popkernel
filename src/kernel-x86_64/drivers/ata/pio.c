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
#include "../../debugging/logging.h"

static void iowait(ATADevice* device) {
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
    inb(device->alt_status_reg);
}

void ATA_software_reset(ATADevice* device) {
    outb(device->dev_ctrl_reg, 0x04); // Software reset bit
    iowait(device);
    outb(device->dev_ctrl_reg, 0);
}

void ATA_identify_device(ATADevice* device) {
    ATA_software_reset(device);
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
        #if DEBUG_ENABLED
        debug_logf(LOG_ERROR, "The ATA device %d %s cannot be identified as a valid ATA device.",
            device->bus, device->slave ? "Slave" : "Master");
        #endif
        return;
    }
}
