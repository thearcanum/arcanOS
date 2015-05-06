global gdt_flush

gdt_flush:
	mov eax, [esp + 4] ; on récupère le pointeur de la GDT
	lgdt [eax]
	
	mov ax, 0x10 ; on update les segments 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	jmp 0x08:reload ; recharge CS
reload:
	ret
