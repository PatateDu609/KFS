%define CR0_PAGING (1 << 31)
%define CR4_PSE (1 << 4)

section .text
	global enable_paging
	global disable_paging
	global flush_tlb
	global flush_cr3

; void enable_paging(int enable_pse)
enable_paging:
	pop ebx

	mov eax, cr0
	or eax, CR0_PAGING
	mov cr0, eax ; enable paging

	cmp ebx, 0
	je ep_ret

	mov eax, cr4
	or eax, CR4_PSE
	mov cr4, eax ; enable PSE (4MB pages)

ep_ret:
	ret


; void disable_paging(void)
disable_paging:
	mov eax, cr0
	and eax, ~CR0_PAGING
	mov cr0, eax ; disable paging
	ret


; void flush_tlb(uint32_t addr)
flush_tlb:
	pop ebx
	invlpg [ebx]
	ret


; void flush_cr3(uint32_t addr)
flush_cr3:
	pop ebx
	mov cr3, ebx
	ret
