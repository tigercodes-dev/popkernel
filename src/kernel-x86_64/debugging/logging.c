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
#include <stdarg.h>
#include <stdbool.h>

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

const char DIGIT_CHARS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void logf_uint(unsigned long long number, int base) {
    char buffer[64];
    int pos = 0;

    do {
        unsigned long long digit = number % base;
        number /= base;
        buffer[pos++] = DIGIT_CHARS[digit];
    } while (number > 0);

    while (--pos >= 0) {
        vgaputc((VGAChar){.chr = buffer[pos], .color = 0x07});
        #if E9_DEBUG_ENABLED
        e9putc(buffer[pos]);
        #endif
    }
}

void logf_int(long long number, int base) {
    if (number < 0) {
        vgaputc((VGAChar){.chr = '-', .color = 0x07});
        #if E9_DEBUG_ENABLED
        e9putc('-');
        #endif

        logf_uint(-number, base);
    } else {
        logf_uint(number, base);
    }
}

typedef enum {
    STATE_NORMAL,
    STATE_LEN,
    STATE_LEN_L,
    STATE_LEN_H,
    STATE_SPEC,
} FmtState;

typedef enum {
    LEN_HH,
    LEN_H,
    LEN_NORMAL,
    LEN_L,
    LEN_LL,
} FmtLength;

void debug_logf(LogLevel level, const char* fmt, ...) {
    vga_print_tag(level);
    #if E9_DEBUG_ENABLED
    e9_print_tag(level);
    #endif

    va_list args;
    va_start(args, fmt);

    FmtState state = STATE_NORMAL;
    FmtLength len = LEN_NORMAL;
    bool number = false;
    bool sign = false;
    int base = 10;
    bool hex_capitalized = false;

    while (*fmt) {
        switch (state) {
            case STATE_NORMAL:
                if (*fmt == '%') {
                    state = STATE_LEN;
                } else {
                    #if E9_DEBUG_ENABLED
                    e9putc(*fmt);
                    #endif
                    vgaputc((VGAChar){.chr = *fmt, .color = 0x07});
                }
                break;
            case STATE_LEN:
                switch (*fmt) {
                    case 'l':
                        len = LEN_L;
                        state = STATE_LEN_L;
                        break;
                    case 'h':
                        len = LEN_H;
                        state = STATE_LEN_H;
                        break;
                    default:
                        state = STATE_SPEC;
                        continue;
                }
                break;
            case STATE_LEN_H:
                if (*fmt == 'h') {
                    len = LEN_HH;
                } else {
                    continue;
                }
                break;
            case STATE_LEN_L:
                if (*fmt == 'l') {
                    len = LEN_LL;
                } else {
                    continue;
                }
                break;
            case STATE_SPEC:
                switch (*fmt) {
                    case 'c':
                        char c = (char)va_arg(args, int);
                        vgaputc((VGAChar){.chr = c, .color = 0x07});
                        #if E9_DEBUG_ENABLED
                        e9putc(c);
                        #endif
                        break;
                    case 's':
                        const char* s = va_arg(args, const char*);
                        vgaputs(s, 0x07);
                        #if E9_DEBUG_ENABLED
                        e9puts(s);
                        #endif
                        break;
                    case '%':
                        vgaputc((VGAChar){.chr = '%', .color = 0x07});
                        #if E9_DEBUG_ENABLED
                        e9putc('%');
                        #endif
                        break;
                    case 'd':
                    case 'i':
                        base = 10;
                        sign = true;
                        number = true;
                        break;
                    case 'u':
                        base = 10;
                        sign = false;
                        number = true;
                        break;
                    case 'X':
                        hex_capitalized = true;
                    case 'x':
                    case 'p':
                        base = 16;
                        sign = false;
                        number = true;
                        break;
                    case 'o':
                        base = 8;
                        sign = false;
                        number = true;
                        break;
                }

                if (number) {
                    if (sign) {
                        switch (len) {
                            case LEN_HH:
                            case LEN_H:
                            case LEN_NORMAL:
                                logf_int(va_arg(args, int), base);
                                break;
                            case LEN_L:
                                logf_int(va_arg(args, long), base);
                                break;
                            case LEN_LL:
                                logf_int(va_arg(args, long long), base);
                                break;
                        }
                    } else {
                        switch (len) {
                            case LEN_HH:
                            case LEN_H:
                            case LEN_NORMAL:
                                logf_uint(va_arg(args, int), base);
                                break;
                            case LEN_L:
                                logf_uint(va_arg(args, long), base);
                                break;
                            case LEN_LL:
                                logf_uint(va_arg(args, long long), base);
                                break;
                        }
                    }
                }

                state = STATE_NORMAL;
                len = LEN_NORMAL;
                base = 10;
                sign = false;
                number = false;

                break;
        }
        fmt++;
    }

    va_end(args);
}
