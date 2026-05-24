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

#ifndef ATAPI_H
#define ATAPI_H

#include "ata.h"

void ATAPI_read_sectors(ATADevice* device, u32 lba, u32 sectors, u16 sector_size, void* buffer);

#endif
