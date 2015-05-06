#ifndef __IO_H
#define __IO_H

#include <types.h>

#define outb(P, D)	outportb(P, D)
#define inb(P)		inportb(P)

uint8_t inportb(uint16_t _port);
void outportb(uint16_t _port,uint8_t _data);


#endif
