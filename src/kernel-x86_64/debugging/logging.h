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

#ifndef DEBUG_LOGGING_H
#define DEBUG_LOGGING_H

#if DEBUG_ENABLED

#include "../drivers/graphics/vga/textmode.h"

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
} LogLevel;

void debug_log(LogLevel level, const char* s);

void debug_logf(LogLevel level, const char* fmt, ...);

#endif

#endif
