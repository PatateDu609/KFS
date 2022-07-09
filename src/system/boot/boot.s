.set ALIGN,			1 << 0
.set MEMINFO,		1 << 1
.set FLAGS,			ALIGN | MEMINFO
.set MAGIC,			0x1BADB002
.set CHECKSUM,		-(MAGIC + FLAGS)

.section			.multiboot
.align				4
.long				MAGIC
.long				FLAGS
.long				CHECKSUM



.section			.bss
.align				16

stack_bottom:
	.skip			16384				# 16KiB

stack_top:



.section			.text
.global				_start
.type				_start, @function

.extern				main
.extern				terminal_initialize

_start:
	mov				$stack_top, %esp
	call			init

	mov				$stack_top, %esp
	call			main				# call main()

	cli
1:	hlt
	jmp				1b

init:
	cli
	call			terminal_initialize


.size				_start, . - _start
