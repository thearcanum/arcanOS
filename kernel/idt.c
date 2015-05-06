#include <idt.h>
#include <screen.h>
#include <system.h>

void idt_init_desc(uint16_t selector, uint32_t offset, uint8_t flags, struct idt_desc *desc)
{
	desc->selector = selector;
	desc->offset0  = offset & 0xFFFF;
	desc->offset1  = (offset & 0xFFFF0000) >> 16;
	desc->reserved = 0x0;
	desc->flags = flags;
}

void idt_init()
{
	int i;

	for(i=0;i<IDT_LEN;i++)
	{
		idt_init_desc(0x08, (uint32_t)&asm_default, _GATE_, &idt[i]);
	}

	_pidt.limit = sizeof(struct idt_desc)*IDT_LEN - 1;
	_pidt.base  = (uint32_t) &idt;

	/* ISR qu'on a implémenté */

	idt_init_desc(0x08, (uint32_t)&asm_clock, _GATE_, &idt[IRQ0]);
	idt_init_desc(0x08, (uint32_t)&asm_kbd, _GATE_, &idt[IRQ1]);

	/* Chargement de l'IDT */
	__asm__ __volatile__("lidt %0" : : "m" (_pidt));

}	

