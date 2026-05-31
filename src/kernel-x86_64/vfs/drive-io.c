/*
    PopKernel OS - x86_64 kernel VFS drive I/O
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

#include "drive-io.h"

#include "../drivers/ata/ata.h"
#include "../drivers/ata/pio.h"
#include "../drivers/ata/atapi.h"

static int IDE_read_sectors(VFS_Drive* drive, u32 lba, u32 count, void* buffer) {
    ATADevice* device = (ATADevice*)drive->drive_desc;
    ATA_identify_device(device);
    if (device->status != 0) return device->status;

    if (device->packet) {
        ATAPI_read_sectors(device, drive->partition_start + lba, count, drive->sector_size, buffer);
        if (device->status != 0) return device->status;
    } else {
        return 1;
    }

    return 0;
}

int VFS_Drive_read_sectors(VFS_Drive* drive, u32 lba, u32 count, void* buffer) {
    switch (drive->type) {
        case DRIVETYPE_IDE:
            return IDE_read_sectors(drive, lba, count, buffer);
        default:
            return 1;
    }
}
