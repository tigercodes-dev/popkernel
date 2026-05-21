/*
    PopKernel OS - x86_64 kernel panic
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

#include "debugging/logging.h"
#include "drivers/graphics/vga/textmode.h"

// From halt.asm
void kernel_halt();

void kernel_panic(const char* msg) {
    #if DEBUG_ENABLED
    debug_logf(LOG_ERROR, "Kernel Panic: %s\n", msg);
    #else
    vgaputs("Kernel Panic! ", 0x04);
    vgaputs(msg, 0x07);
    vgaputc((VGAChar){.chr = '\n', .color = 0x07});
    #endif

    vgaputs("The system cannot continue and will halt.\n", 0x07);
    kernel_halt();
}