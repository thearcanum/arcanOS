#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <types.h>

void memset(char *ptr, int value, uint32_t size);
void memset16(uint16_t *ptr, uint16_t value, uint32_t size);
void memset32(uint32_t *ptr, uint32_t value, uint32_t size);
void memcpy(char *dest, char *src, uint32_t size);

void _cli();
void _sti();

uint32_t strlen(char *s);
uint32_t strcmp(char *s, char *m);

uint8_t _clock;

#endif
