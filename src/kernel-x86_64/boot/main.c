/*
    PopKernel OS - x86_64 kernel after long mode setup
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

#include "../drivers/graphics/vga/textmode.h"
#include "../debugging/logging.h"

extern u8 _kernel_load;

// Kernel initialization
void kmain() {
    clear_screen();
    debug_logf(LOG_INFO, "Kernel loaded at 0x%p\n", &_kernel_load);
    for (;;);
}