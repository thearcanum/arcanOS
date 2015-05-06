#include <pic.h>

void pic_init()
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	outb(0x21, 0x20);
	outb(0xA1, 0x70);	

	outb(0x21, 0x04);
	outb(0xA1, 0x02);

	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	_pit_init();
}

/* Change la fréquence */

void _pit_init()
{
	uint32_t div = 1193180U/_FREQ_;
	uint8_t div_low, div_high;

	outb(PIT_COM, 0x36);

	div_low 	= (div & 0xFF);
	div_high 	= (div & 0xFF00) >> 8; 

	outb(PIT_CH0, div_low);
	outb(PIT_CH0, div_high);
}
