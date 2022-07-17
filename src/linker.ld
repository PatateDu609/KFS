ENTRY(_start)

PHDRS
{
	text PT_LOAD FILEHDR;
	readonly PT_LOAD;
	data PT_LOAD;
}

SECTIONS
{
	. = 1M;
	start = .;

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
		*(.bss*)
	} :data

	end = .; /* end of kernel */
}
