/*
    PopKernel OS - x86_64 kernel ATA
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

#ifndef ATA_DRIVER_H
#define ATA_DRIVER_H

#include <integers.h>
#include <stdbool.h>

typedef struct {
    int bus;
    bool slave;

    bool packet;
    bool sata;

    int status;
    
    u16 data_reg;
    union {
        u16 error_reg;
        u16 features_reg;
    };
    u16 sector_count_reg;
    u16 lba_low_reg;
    u16 lba_mid_reg;
    u16 lba_high_reg;
    u16 drive_head_reg;
    union {
        u16 status_reg;
        u16 command_reg;
    };
    union {
        u16 alt_status_reg;
        u16 dev_ctrl_reg;
    };
    u16 drive_addr_reg;

    u16 buffer[256];
} ATADevice;

extern ATADevice* ATA_primary_master;
extern ATADevice* ATA_primary_slave;
extern ATADevice* ATA_secondary_master;
extern ATADevice* ATA_secondary_slave;

#endif
