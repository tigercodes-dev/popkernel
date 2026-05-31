/*
    PopKernel OS - x86_64 kernel virtual file system
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

#include "vfs.h"
#include "../string.h"
#include <stddef.h>

VFS_File handles[FILE_HANDLES_MAX];

void VFS_setup() {
    for (int i = 0; i < FILE_HANDLES_MAX; i++) {
        handles[i].open = false;
    }

    // stdin
    handles[0].drive = NULL;
    handles[0].file_desc = NULL;
    handles[0].open = true;
    handles[0].file_size = 0;
    handles[0].file_seek = 0;
    handles[0].permissions = 0x0444;
    handles[0].owner = 0;
    handles[0].group = 0;
    handles[0].type = FILETYPE_DATASTREAM;
    strcpy(handles[0].name, "stdin");

    // stdout
    handles[1].drive = NULL;
    handles[1].file_desc = NULL;
    handles[1].open = true;
    handles[1].file_size = 0;
    handles[1].file_seek = 0;
    handles[1].permissions = 0x0222;
    handles[1].owner = 0;
    handles[1].group = 0;
    handles[1].type = FILETYPE_DATASTREAM;
    strcpy(handles[1].name, "stdout");

    // stderr
    handles[2].drive = NULL;
    handles[2].file_desc = NULL;
    handles[2].open = true;
    handles[2].file_size = 0;
    handles[2].file_seek = 0;
    handles[2].permissions = 0x0222;
    handles[2].owner = 0;
    handles[2].group = 0;
    handles[2].type = FILETYPE_DATASTREAM;
    strcpy(handles[2].name, "stderr");
}
