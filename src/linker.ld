OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)

KERN_START = 0xC0000000;
PHYS_START = 1M;
SECTIONS
{
	. = PHYS_START;
	ld_start = .;

	.multiboot.data ALIGN(4K) : {
		KEEP(*(.multiboot.data))
	}

	.multiboot.text ALIGN(4K) : {
		*(.multiboot.text)
	}

	. += KERN_START;

	.text ALIGN(4K): AT(ADDR(.text) - KERN_START)
	{
		*(.text*)
	}


	.rodata ALIGN(4K) : AT(ADDR(.rodata) - KERN_START)
	{
		*(.rodata*)
	}

	.data ALIGN(4K) : AT(ADDR(.data) - KERN_START)
	{
		*(.data*)
	}

	.bss ALIGN(4K) : AT(ADDR(.bss) - KERN_START)
	{
		sbss = .;
		*(COMMON*)
		*(.bss*)
		ebss = .;
	}

	ld_end = .;
}
