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
#include "gdt.h"
#include "../interrupts/idt.h"
#include "../interrupts/isr.h"
#include "../interrupts/hardware/irq.h"
#include "../interrupts/interrupt-control.h"
#include "../drivers/ata/pio.h"
#include "../drivers/ata/atapi.h"

extern u8 _kernel_load;

void timer_handler(struct InterruptStack* stack) {
    vgaputc((VGAChar){.chr = '.', .color = 0x07});
}

// Kernel initialization
void kmain() {
    disable_interrupts();
    
    clear_screen();
    #if DEBUG_ENABLED
    debug_logf(LOG_INFO, "Kernel loaded at 0x%p\n", &_kernel_load);
    #endif

    GDT_setup();
    IDT_setup();

    ISR_setup_interrupts();
    IRQ_setup(32);
    enable_interrupts();

    IRQ_set_handler(0, timer_handler);

    ATA_setup_irqs();

    ATADevice* device = ATA_secondary_master;
    ATA_identify_device(device);

    if (device->status != 0) {
        #if DEBUG_ENABLED
        debug_logf(LOG_ERROR, "Error %u occured while identifying the CD-ROM device.\n", device->status);
        #endif
        goto end;
    }

    u8* read_buf = (u8*)0x400000;

    ATAPI_read_sectors(device, 0, 1, 2048, read_buf);
    if (device->status != 0) {
        #if DEBUG_ENABLED
        debug_logf(LOG_ERROR, "Error %u occured while reading the CD-ROM device.\n", device->status);
        #endif
        goto end;
    }

    end:
    for (;;);
}