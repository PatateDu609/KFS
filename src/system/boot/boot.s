bits 32

%define KERN_START          0xC0000000
%define VGA_ADDR            0x000B8000
%define GDT_ADDR            0x00000800
%define V2P(addr)           addr - KERN_START
%define PAGE_TABLE_NB       1024
%define FRAME_SIZE          4096
%define VIRT_ADDR_MASK      0xFFFFF000
%define GET_VIRT_ADDR(addr) (addr & VIRT_ADDR_MASK)

%define PAGE_TABLE_READ_WRITE (1 << 1)
%define PAGE_TABLE_PRESENT (1)

section				.multiboot.text
global _start:function
_start:
	mov eax, V2P(boot_page_directory)     ; take the physical address of the page directory
	mov ebx, V2P(boot_first_table)        ; take the physical address of the first page table

page_directory_init:
	mov edi, dword 0

page_directory_loop:
	cmp edi, 4 * PAGE_TABLE_NB
	jge page_directory_init_next            ; pursues the page directory init

	mov esi, edi
	shl esi, 10                             ; Equivalent to esi *= 1024

	and esi, VIRT_ADDR_MASK
	mov ecx, [ebx + edi]
	or ecx, esi
	mov [ebx + edi], ecx

	; Avoids the insanity of doing the increment by pure assembly
	times 4 inc edi

	jmp page_directory_loop

page_directory_init_next:                   ; sets specific page config
	mov edi, ebx
	and edi, VIRT_ADDR_MASK
	or edi, PAGE_TABLE_READ_WRITE | PAGE_TABLE_PRESENT
	mov [eax + 0], edi
    mov [eax + 768 * 4], edi

enable_paging:
	mov cr3, eax

	mov edi, cr0
	or edi, 0x80000000                      ; set PG bit in cr0 register
	mov cr0, edi

	lea edi, [higher_half]
	jmp edi

; From there, paging is enabled, we can use it, but some more configuration may be needed.
section .text

extern				_preinit
extern				main
extern				terminal_initialize
extern				init_gdt
extern				init_idt
extern				init_pic
extern				init_physical
extern              finalize_paging_setup

higher_half:
	mov             dword [boot_page_directory], PAGE_TABLE_READ_WRITE
	invlpg          [0]
	mov				esp, stack_top
	call            finalize_paging_setup

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
	; call			init_physical

	sti 								; enable interrupts
	ret


section				.bss
stack_bottom:
	resb				16384			; 16MB of stack space
	align				16
stack_top:

section             .data
align FRAME_SIZE

global boot_page_directory:data
boot_page_directory:
	times PAGE_TABLE_NB dd dword (PAGE_TABLE_READ_WRITE)

static boot_first_table:data
boot_first_table:
	times PAGE_TABLE_NB dd dword (PAGE_TABLE_READ_WRITE | PAGE_TABLE_PRESENT)
