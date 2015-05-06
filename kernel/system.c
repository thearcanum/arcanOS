#include <system.h>

void _cli()
{
	asm("cli" ::);
}

void _sti()
{
	asm("sti" ::);
}

void memset(char* ptr, int value, uint32_t size)
{
	int i;
	for(i=0;i<size;i++) 
		ptr[i] = value;
}

void memset16(uint16_t *ptr, uint16_t value, uint32_t size)
{
	int i;
	for(i=0;i<size;i++)
		ptr[i] = value;
}

void memset32(uint32_t *ptr, uint32_t value, uint32_t size)
{
	int i;
	for(i=0;i<size;i++)
		ptr[i] = value;
}



void memcpy(char *dest, char *src, uint32_t size)
{
	int i;
	for(i=0;i<size;i++)
		dest[i] = src[i];
}


uint32_t strlen(char *s)
{
	uint32_t l = 0;
	while(*s) {
		s++;
		l++;
	}
	return l;
}

uint32_t strcmp(char *s, char *m)
{
	uint32_t diff = 0;
	while(*s) {
		diff += (*s - *m); 
		if(diff > 0)
			return diff;
		s++;	
		m++;	
	}
	return 0;
}
