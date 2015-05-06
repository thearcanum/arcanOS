#ifndef __SCREEN_H
#define __SCREEN_H

#include <system.h>

#define WIDTH	80
#define HEIGHT	25

uint16_t *videoptr;
uint8_t   attribut;
uint32_t  cx, cy;

void init_video();
void clears();
void move_cursor();
void scroll_down();
void printk (const char *format, ...);

void __pok();

#endif
