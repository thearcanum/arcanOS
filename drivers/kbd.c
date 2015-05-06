#include <idt.h>
#include <screen.h>
#include <system.h>
#include <io.h>

#define KBDP0	0x60

char cbuff[0xFF] = {0};
uint8_t cs = 0;

uint8_t KBD[0xFF] =
{
	0x0, 0x0, '&', '2', '\"', '\'', '(', '-',
	'7','_', '9', '0', ')', '=', '\r', 0x0,
	'a', 'z', 'e', 'r', 't', 'y', 'u', 'i',
	'o', 'p', '^', '$', '\n', 0x0, 'q', 's',
	'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
	'%', '*', 0x0, 0x0, 'w', 'x', 'c', 'v',
	'b', 'n', ',', ';', ':', 0x0, 0x0, 0x0,
	0x0, ' ', 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};

uint8_t get_maj(uint8_t v)
{
	switch(v)
	{
		default: return 0;

		case ':': return '/';
		case ';': return '.';
		case '\r': return '\r';
		case '\n': return '\n';
		case '&': return '1';
		case '2': return '2';
		case '\"': return '3';
		case '\'': return '4';
		case '(': return '5';
		case '-': return '6';
		case '7': return '7';
		case '_': return '8';
		case '9': return '9';
		case '0': return '0';
		case ')': return ')';
		case '=': return '+';
	}

	return 0;
}

void isr_kbd()
{
	uint8_t sc = 0x0, v = 0;
	static int maj = 0;

	do {
	    sc = inb(KBDP0+4);
	} while((sc & 0x01) == 0);

	sc = inb(KBDP0);

	if(KBD[sc]) {
		v = KBD[sc];
		if(maj && (v >= 'a') && (v <= 'z')) v += ('A' - 'a');
		else {
			if(maj)
				v = get_maj(v);
		} 

		cbuff[cs++] = v;
		printk("%c", v);

		if(v == '\n')
		{
			/* send command */
			memset(cbuff, 0, cs);
			cs = 0;
		}
		
	}
	else {
		switch(sc) {
		default: /* On connait pas */
			break;
		case 0x3A:
			maj = ~maj;
			break;

		}
	}
}
