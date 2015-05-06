#include <idt.h>
#include <system.h>
#include <screen.h>

void isr_default()
{
	/* HEU */
	printk("Interruption sans handler !\n");
}

void isr_clock()
{
	static uint32_t ticks = 0;
	ticks++;

	if((ticks % 100) == 0)
	{
		/* 1 sec */
		ticks = 0;
	}	
}

