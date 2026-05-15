#include "textmode.h"
#include "../../../io.h"

VGAChar* vgabuffer = (VGAChar*)0xB8000;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

int screenX = 0;
int screenY = 0;

// Move the cursor to (screenX, screenY)
void upd_cursor() {
    int pos = screenY * VGA_HEIGHT + screenX;

    outb(0x3D4, 0xF);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0xE);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
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
    int pos = screenY * VGA_HEIGHT + screenX;
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
            break;
    }
    screenX++;

    if (screenX >= VGA_WIDTH) {
        screenX = 0;
        screenY++;
    }

    upd_cursor();
}
