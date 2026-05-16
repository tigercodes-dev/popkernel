/*
    PopKernel OS - x86_64 kernel loggging
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

#include "logging.h"
#include "e9.h"

#define E9_DEBUG_ENABLED 1

void vga_print_tag(LogLevel level) {
    switch (level) {
        case LOG_DEBUG:
            vgaputs("[DEBUG]:", 0x0F);
            break;
        case LOG_INFO:
            vgaputs("[INFO]:", 0x03);
            break;
        case LOG_WARN:
            vgaputs("[WARNING]:", 0x0E);
            break;
        case LOG_ERROR:
            vgaputs("[ERROR]:", 0x04);
            break;
    }
    vgaputc((VGAChar){.chr = ' ', .color = 0x07});
}

void e9_print_tag(LogLevel level) {
    switch (level) {
        case LOG_DEBUG:
            e9puts("\e[1;37m[DEBUG]:\e[0m ");
            break;
        case LOG_INFO:
            e9puts("\e[36m[INFO]:\e[0m ");
            break;
        case LOG_WARN:
            e9puts("\e[1;33m[WARNING]:\e[0m ");
            break;
        case LOG_ERROR:
            e9puts("\e[31m[ERROR]:\e[0m ");
            break;
    }
}

void debug_log(LogLevel level, const char* s) {
    vga_print_tag(level);
    vgaputs(s, 0x07);
    
    #if E9_DEBUG_ENABLED
    e9_print_tag(level);
    e9puts(s);
    #endif
}
