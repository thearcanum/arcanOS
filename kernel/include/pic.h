#ifndef __PIC_H
#define __PIC_H

#include <types.h>
#include <io.h>

/* TODO : Gestion propre et efficace du PIC ... */

#define _FREQ_	100

#define PIT_CH0		0x40
#define PIT_CH1		0x41
#define PIT_CH2		0x42
#define PIT_COM		0x43

void pic_init();
void _pit_init();

#endif
