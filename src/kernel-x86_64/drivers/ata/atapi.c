/*
    PopKernel OS - x86_64 kernel ATA packet interface
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

#include "atapi.h"
#include "delay.h"
#include "../../io.h"

#define CMD_PACKET 0xA0

#include "../../debugging/logging.h"

void ATAPI_read_sectors(ATADevice* device, u32 lba, u32 sectors, u16 sector_size, void* buffer) {
    outb(device->drive_head_reg, 0xA0 | (device->slave << 4));
    iowait(device);
    outb(device->features_reg, 0);
    outb(device->lba_mid_reg, sector_size & 0xFF);
    outb(device->lba_high_reg, (sector_size >> 8) & 0xFF);
    outb(device->command_reg, CMD_PACKET);
    iowait(device);
    
    u8 status;
    do {
        status = inb(device->status_reg);
        iowait(device);
    } while ((status & 0x01) == 0 && ((status & 0x80) != 0 || (status & 0x08) == 0));

    if (status & 0x01 != 0) {
        device->status = 2;
        return;
    }

    volatile u8 packet[12] = {
        0xA8, 0,
        (lba >> 24) & 0xFF, (lba >> 16) & 0xFF, (lba >> 8) & 0xFF, lba & 0xFF,
        (sectors >> 24) & 0xFF, (sectors >> 16) & 0xFF, (sectors >> 8) & 0xFF, sectors & 0xFF,
        0, 0
    };

    for (int i = 0; i < 6; i++) {
        outw(device->data_reg, *(u16*)(&packet[i * 2]));
    }

    for (u32 i = 0; i < sectors; i++) {
        do {
            status = inb(device->status_reg);
            iowait(device);
        } while ((status & 0x01) == 0 && ((status & 0x80) != 0 || (status & 0x08) == 0));
        if (status & 0x01 != 0) {
            device->status = 2;
            return;
        }

        u16 size = (inb(device->lba_high_reg) << 8) | inb(device->lba_mid_reg);

        u16* u16buf = (u16*)buffer;
        for (int j = 0; j < size / 2; j++) {
            u16buf[(i * sector_size) / 2 + j] = inw(device->data_reg);
        }
    }

    device->status = 0;
}
