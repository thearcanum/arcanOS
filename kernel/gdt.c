#include <gdt.h>

/* charge la gdt et update les segments, dans gdt.s */
extern void gdt_flush(uint32_t); 

void gdt_init_desc(uint32_t base, uint32_t limit, uint8_t access, uint8_t flag, struct gdt_entry *gdt_e)
{
	gdt_e->limit0 = limit & 0xFFFF;
	gdt_e->base0 = base & 0xFFFFFF;
	gdt_e->access = access;
	gdt_e->limit1 = (limit & 0x0F0000) >> 16;
	gdt_e->flags = flag;
	gdt_e->base1 = (base & 0xFF000000) >> 24;
}

void gdt_init()
{
	pgdt.limit = sizeof(struct gdt_entry)*GDT_LEN - 1;
	pgdt.base = (uint32_t) &gdt[0];
	
	gdt_init_desc(0, 0xFFFFFFFF, 0x9A, 0xCF, &gdt[1]); /* code */
	gdt_init_desc(0, 0xFFFFFFFF, 0x92, 0xCF, &gdt[2]); /* data */
	gdt_init_desc(0, 0xFFFFFFFF, 0xFA, 0xCF, &gdt[3]); 
	gdt_init_desc(0, 0xFFFFFFFF, 0xF2, 0xCF, &gdt[4]); 
	
	gdt_flush((uint32_t)&pgdt);
}
