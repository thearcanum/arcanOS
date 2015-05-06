#ifndef __CPUID_H
#define __CPUID_H

#include <screen.h>
 
enum cpuid_requests {

  CPUID_GETVENDORSTRING,
  CPUID_GETFEATURES,
  CPUID_GETTLB,
  CPUID_GETSERIAL,
 
  CPUID_INTELEXTENDED=0x80000000,
  CPUID_INTELFEATURES,
  CPUID_INTELBRANDSTRING,
  CPUID_INTELBRANDSTRINGMORE,
  CPUID_INTELBRANDSTRINGEND,
};
 

static inline void cpuid(int code, uint32_t *a, uint32_t *d) {
  asm volatile("cpuid":"=a"(*a),"=d"(*d):"a"(code):"ecx","ebx");
}
 
/** issue a complete request, storing general registers output as a string
 */
static inline int cpuid_string(int code, uint32_t where[4]) {
  asm volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
               "=c"(*(where+2)),"=d"(*(where+3)):"a"(code));
  return (int)where[0];
}

void cpu_vendor()
{
	uint32_t str[4];

	cpuid_string(CPUID_GETVENDORSTRING, str);

	printk("CPU : ");
	printk("%c%c%c%c", str[1] & 0xFF, (str[1] & 0xFF00) >> 8,
						  (str[1] & 0xFF0000) >> 16, (str[1] & 0xFF000000) >> 24);
	printk("%c%c%c%c", str[3] & 0xFF, (str[3] & 0xFF00) >> 8,
						  (str[3] & 0xFF0000) >> 16, (str[3] & 0xFF000000) >> 24);
	printk("%c%c%c%c", str[2] & 0xFF, (str[2] & 0xFF00) >> 8,
						  (str[2] & 0xFF0000) >> 16, (str[2] & 0xFF000000) >> 24);
	printk("\n");
}

#endif



