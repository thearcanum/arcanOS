#ifndef __IDT_H
#define __IDT_H

#include <system.h>
 
#define IDT_LEN		256

#define IDT_16BIT  0x6 /* 00000110 */
#define IDT_32BIT  0xE /* 00001110 */

#define IDT_DPL_RING_0  0
#define IDT_DPL_RING_1  (1 << 5) /* 00100000 */
#define IDT_DPL_RING_2  (1 << 6) /* 01000000 */
#define IDT_DPL_RING_3  (3 << 5) /* 01100000 */

#define IDT_SEGMENT_PRESENT    0x80 /* 10000000 */

#define _GATE_	(IDT_32BIT | IDT_DPL_RING_0 | IDT_SEGMENT_PRESENT)

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

struct idt_desc
{
	uint16_t offset0;
	uint16_t selector;
	uint8_t reserved;
	uint8_t flags;
	uint16_t offset1;
} __attribute__((packed));

struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)); // Comme pour la GDT on va le charger avec LIDT 

extern void asm_default();
extern void asm_clock();
extern void asm_kbd();

void isr_default();
void isr_clock();
void isr_kbd();

struct idt_desc idt[IDT_LEN];
struct idt_ptr _pidt;

void idt_init_desc(uint16_t selector, uint32_t offset, uint8_t flags, struct idt_desc *desc);
void idt_init();

#endif
