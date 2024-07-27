//
// Created by Adithiya Venkatakrishnan on 27/07/2024.
//

#ifndef IRQ_H
#define IRQ_H

#include <idt/isr.h>
#include <modules/modules.h>

void irq_install(u32 i, void (*handler)(struct registers*));
void irq_init();

#endif //IRQ_H
