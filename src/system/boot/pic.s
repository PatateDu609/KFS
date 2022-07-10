%define PIC1			0x20
%define PIC2			0xA0
%define PIC1_COMMAND	PIC1
%define PIC1_DATA		(PIC1 + 1)
%define PIC2_COMMAND	PIC2
%define PIC2_DATA		(PIC2 + 1)

%define PIC_EOI			0x20

; ICW4 (not) needed
%define ICW1_ICW4			0x01
; Single (cascade) mode
%define ICW1_SINGLE			0x02
; Call address interval 4 (8)
%define ICW1_INTERVAL4		0x04
; Level triggered (edge) mode
%define ICW1_LEVEL			0x08
; Initialization - required!
%define ICW1_INIT			0x10

; 8086/88 (MCS-80/85) mode
%define ICW4_8086			0x01
; Auto (normal) EOI
%define ICW4_AUTO			0x02
; Buffered mode/slave
%define ICW4_BUF_SLAVE		0x08
; Buffered mode/master
%define ICW4_BUF_MASTER		0x0C
; Special fully nested (not)
%define ICW4_SFNM			0x10

global init_pic
global pic_send_eoi

section .text

; void init_pic(int offset1, int offset2);
init_pic:
	mov bl, 0x20		; offset1
	mov cl, 0x28		; offset2



	; ICW1: Master PIC starts initialization
	mov al, (ICW1_INIT | ICW1_ICW4) ; 0x11
	out PIC1_COMMAND, al
	mov al, (ICW1_INIT | ICW1_ICW4) ; 0x11
	out PIC2_COMMAND, al
	; ICW2: PIC1 offset
	mov al, bl
	out PIC1_DATA, al
	mov al, cl
	out PIC2_DATA, al
	; ICW3: PIC1 connected to PIC2 (slave)
	mov al, 4
	out PIC1_DATA, al
	mov al, 2
	out PIC2_DATA, al
	; ICW4: PIC1 8086 mode
	mov al, (ICW4_8086)
	out PIC1_DATA, al
	mov al, (ICW4_8086)
	out PIC2_DATA, al

	; Mask all interrupts
	mov al, 0xff
	out PIC1_DATA, al
	mov al, 0xff
	out PIC2_DATA, al

	ret

; void pic_send_eoi(int irq);
pic_send_eoi:
	mov bl, [esp + 4]

	cmp bl, 8
	jl __pic_send_eoi_master

	mov al, PIC_EOI
	out PIC2_COMMAND, al

__pic_send_eoi_master:
	mov al, PIC_EOI
	out PIC1_COMMAND, al

	ret
