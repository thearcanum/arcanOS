#ifndef __GDT_H
#define __GDT_H

#include <types.h>

#define GDT_LEN	5

struct gdt_entry
{
	uint16_t limit0;
	uint32_t base0 : 24;	
	uint8_t access	: 8;
	uint8_t limit1	: 4;
	uint8_t flags	: 4;
	uint8_t base1;
} __attribute__((packed));

struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));



struct gdt_entry gdt[GDT_LEN]; /* NULL + CODE + DATA + ... */
struct gdt_ptr pgdt;

void gdt_init();

#endif
