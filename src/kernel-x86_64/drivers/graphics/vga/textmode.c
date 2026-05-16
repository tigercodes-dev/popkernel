/*
    PopKernel OS - x86_64 kernel VGA textmode
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

#include "textmode.h"
#include "../../../io.h"

VGAChar* vgabuffer = (VGAChar*)0xB8000;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

int screenX = 0;
int screenY = 0;

// Move the cursor to (screenX, screenY)
void upd_cursor() {
    int pos = screenY * VGA_WIDTH + screenX;

    outb(0x3D4, 0xF);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0xE);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

// Scroll the screen up one line
void scroll_up() {
    for (int y = 0; y < VGA_HEIGHT - 1; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vgabuffer[y * VGA_WIDTH + x] = vgabuffer[(y + 1) * VGA_WIDTH + x];
        }
    }

    for (int x = 0; x < VGA_WIDTH; x++) {
        vgabuffer[VGA_WIDTH * (VGA_HEIGHT - 1) + x] = (VGAChar){.chr = 0, .color = 0x07};
    }
}

void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vgabuffer[i] = (VGAChar){.chr = 0, .color = 0x07};
    }
    screenX = 0;
    screenY = 0;
    upd_cursor();
}

void vgaputc(VGAChar c) {
    int pos = screenY * VGA_WIDTH + screenX;
    switch (c.chr) {
        case '\n':
            screenX = 0;
            screenY++;
            break;
        case '\r':
            screenX = 0;
            break;
        default:
            vgabuffer[pos] = c;
            screenX++;
            break;
    }

    if (screenX >= VGA_WIDTH) {
        screenX = 0;
        screenY++;
    }

    if (screenY >= VGA_HEIGHT) {
        scroll_up();
        screenY--;
    }

    upd_cursor();
}

void vgaputs(const char* s, u8 color) {
    while (*s) {
        vgaputc((VGAChar){.chr = *s, .color = color});
        s++;
    }
}
