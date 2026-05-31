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

#ifndef VFS_H
#define VFS_H

#include <integers.h>
#include <stdbool.h>

#define MAX_PATH_LEN 512
#define FILE_HANDLES_MAX 32

typedef enum {
    DRIVETYPE_IDE,
    DRIVETYPE_SATA,
} VFS_DriveType;

typedef enum {
    FILESYSTEM_ISO,
    FILESYSTEM_FAT,
} VFS_Filesystem;

typedef struct {
    VFS_DriveType type;
    VFS_Filesystem filesystem;
    int device_id;
    int sector_size;
    void* drive_desc;
    void* fs_desc;
    int partition_num;
    u32 partition_start;
    u32 partition_size;
    char name[16];
} VFS_Drive;

typedef enum {
    FILETYPE_DATASTREAM,
    FILETYPE_FILE,
    FILETYPE_DIRECTORY,
    FILETYPE_SYMLINK,
} VFS_FileType;

typedef struct {
    VFS_Drive* drive;
    void* file_desc;
    bool open;
    u64 file_size;
    u64 file_seek;
    u16 permissions;
    u32 owner;
    u32 group;
    VFS_FileType type;
    char name[MAX_PATH_LEN];
} VFS_File;

extern VFS_File handles[FILE_HANDLES_MAX];

extern VFS_File* stdin;
extern VFS_File* stdout;
extern VFS_File* stderr;

void VFS_setup();

#endif
