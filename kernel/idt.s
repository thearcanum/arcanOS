extern isr_default, isr_clock, isr_kbd

global asm_default, asm_clock, asm_kbd

asm_default:
	call isr_default
	mov al, 0x20 ; fin d'interruption
	out 0x20, al
	iret ; on retourne

asm_clock:
	call isr_clock
	mov al, 0x20
	out 0x20, al
	iret

asm_kbd:
	call isr_kbd
	mov al, 0x20
	out 0x20, al
	iret
