ENTRY(_start)

PHDRS
{
	headers PT_PHDR PHDRS;
	text PT_LOAD FILEHDR PHDRS;
	readonly PT_LOAD;
	data PT_LOAD;
}

SECTIONS
{
	ld_start = 1M;
	. = ld_start;

	.text BLOCK(4K) : ALIGN(4K)
	{
		KEEP(*(.multiboot))
		*(.text*)
	} :text

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata*)
	} :readonly

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data*)
	} :data

	.bss BLOCK(4K) : ALIGN(4K)
	{
		sbss = .;
		*(COMMON*)
		*(.bss*)
		ebss = .;
		ld_end = .;
	} :data
}
