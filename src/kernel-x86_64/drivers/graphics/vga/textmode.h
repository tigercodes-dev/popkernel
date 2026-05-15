#ifndef VGA_TEXTMODE_H
#define VGA_TEXTMODE_H

#include <integers.h>

typedef struct {
    char chr;
    u8 color;
} __attribute__((packed)) VGAChar;

// Clear the VGA text mode screen.
void clear_screen();

// Print a character to the VGA screen at the current cursor position.
void vgaputc(VGAChar c);

#endif
