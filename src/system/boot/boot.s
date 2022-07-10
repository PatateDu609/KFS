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



section				.bss
resb				16384 ; 16MB of stack space
align				16
stack_top:



section				.text
global				_start

extern				main
extern				terminal_initialize
extern				init_gdt
extern				init_idt
extern				init_pic

_start:
	mov				esp, stack_top
	call			init

	call			main				; call main()

	cli
	hlt

init:
	cli									; clear interrupts
	call			init_gdt
	call			init_pic
	call			init_idt
	call			terminal_initialize

	sti 								; enable interrupts
	ret
