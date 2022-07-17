bits 32

%define ALIGN			1 << 0
%define MEMINFO			1 << 1
%define FLAGS			ALIGN | MEMINFO
%define MAGIC			0x1BADB002
%define CHECKSUM		-(MAGIC + (FLAGS))

section				.multiboot
	align			4
	dd				MAGIC
	dd				FLAGS
	dd				CHECKSUM



section				.text
global				_start

extern				_preinit
extern				main
extern				terminal_initialize
extern				init_gdt
extern				init_idt
extern				init_pic

_start:
	mov				esp, stack_top

	push			ebx					; Pushing to the stack the multiboot info structure address
	push			eax					; Pushing to the stack the magic number
	call			_preinit			; Read in the multiboot info structure

	call			init

	call			main				; call main()

	cli
	hlt

init:
	cli									; clear interrupts
	call			init_gdt
	call			init_pic
	call			init_idt

	sti 								; enable interrupts
	ret


section				.bss
	resb				16384			; 16MB of stack space
	align				16
	stack_top:
