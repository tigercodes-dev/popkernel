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

#include "ata.h"

static ATADevice _primary_master_ = {
    .bus = 1,
    .slave = false,
    .packet = false, // We dont know if it is packet or sata until identify
    .sata = false,
    .status = 0,
    .data_reg = 0x1F0,
    .error_reg = 0x1F1, // Also sets features reg
    .sector_count_reg = 0x1F2,
    .lba_low_reg = 0x1F3,
    .lba_mid_reg = 0x1F4,
    .lba_high_reg = 0x1F5,
    .drive_head_reg = 0x1F6,
    .status_reg = 0x1F7, // Also sets command reg
    .dev_ctrl_reg = 0x3F6,
    .drive_addr_reg = 0x3F7,
};
ATADevice* ATA_primary_master = &_primary_master_;

static ATADevice _primary_slave_ = {
    .bus = 1,
    .slave = true,
    .packet = false, // We dont know if it is packet or sata until identify
    .sata = false,
    .status = 0,
    .data_reg = 0x1F0,
    .error_reg = 0x1F1, // Also sets features reg
    .sector_count_reg = 0x1F2,
    .lba_low_reg = 0x1F3,
    .lba_mid_reg = 0x1F4,
    .lba_high_reg = 0x1F5,
    .drive_head_reg = 0x1F6,
    .status_reg = 0x1F7, // Also sets command reg
    .dev_ctrl_reg = 0x3F6,
    .drive_addr_reg = 0x3F7,
};
ATADevice* ATA_primary_slave = &_primary_slave_;

static ATADevice _secondary_master_ = {
    .bus = 2,
    .slave = false,
    .packet = false, // We dont know if it is packet or sata until identify
    .sata = false,
    .status = 0,
    .data_reg = 0x170,
    .error_reg = 0x171, // Also sets features reg
    .sector_count_reg = 0x172,
    .lba_low_reg = 0x173,
    .lba_mid_reg = 0x174,
    .lba_high_reg = 0x175,
    .drive_head_reg = 0x176,
    .status_reg = 0x177, // Also sets command reg
    .dev_ctrl_reg = 0x376,
    .drive_addr_reg = 0x377,
};
ATADevice* ATA_secondary_master = &_secondary_master_;

static ATADevice _secondary_slave_ = {
    .bus = 2,
    .slave = true,
    .packet = false, // We dont know if it is packet or sata until identify
    .sata = false,
    .status = 0,
    .data_reg = 0x170,
    .error_reg = 0x171, // Also sets features reg
    .sector_count_reg = 0x172,
    .lba_low_reg = 0x173,
    .lba_mid_reg = 0x174,
    .lba_high_reg = 0x175,
    .drive_head_reg = 0x176,
    .status_reg = 0x177, // Also sets command reg
    .dev_ctrl_reg = 0x376,
    .drive_addr_reg = 0x377,
};
ATADevice* ATA_secondary_slave = &_secondary_slave_;
