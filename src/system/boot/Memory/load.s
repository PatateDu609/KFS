%define CR0_PAGING (1 << 31)

section .text
	global enable_paging
	global disable_paging
	global flush_tlb
	global flush_cr3
	global reset_cr3

; void enable_paging(void)
enable_paging:
	mov eax, cr0
	or eax, CR0_PAGING
	mov cr0, eax ; enable paging
	ret


; void disable_paging(void)
disable_paging:
	mov eax, cr0
	and eax, ~CR0_PAGING
	mov cr0, eax ; disable paging
	ret


; void flush_tlb(uint32_t idx)
flush_tlb:
	pop ebx
	invlpg [ebx]
	ret


; void flush_cr3(uint32_t addr)
flush_cr3:
	mov ebx, [esp + 4]
	mov cr3, ebx
	ret

; void reset_cr3(void)
reset_cr3:
	mov ebx, cr3
	mov cr3, ebx
	ret
