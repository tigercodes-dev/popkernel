/*
    PopKernel OS - x86_64 kernel 8259 PIC driver
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

#ifndef PIC_8259_H
#define PIC_8259_H

#include <integers.h>

void PIC_8259_setup(int remap_offset);

void PIC_8259_enable();
void PIC_8259_disable();

void PIC_8259_mask(int irq);
void PIC_8259_unmask(int irq);

void PIC_8259_EOI(int irq);

u16 PIC_8259_get_IRR();
u16 PIC_8259_get_ISR();

#endif
