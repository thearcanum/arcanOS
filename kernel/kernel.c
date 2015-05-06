#include <kernel.h>
#include <cpuid.h>

void kernel_main(multiboot_info_t *mbi)
{		
	_cli();
	init_video();
	printk("=== Arcanum kernel ===\n");

	printk("Chargement de la GDT... ");
	gdt_init();
	__pok();
	
	printk("Chargement de l'IDT... ");
	idt_init();
	pic_init();
	_clock = 0;

	__pok();

	printk("Activation des interruptions. \n");
	_sti();
	

	for(;;) {}
}
