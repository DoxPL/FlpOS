org 7C00h

jmp short start

Text:	db "Booting in progress... "
Date:	db "[ RTC Placeholder ]"
EndTxt:

; Real mode
; 16-bit addressing
; Use BIOS interrupts

start:
	mov bx, 0005h
	mov cx, 1
	xor dx, dx
	mov ds, dx
	cld

clear_screen:
	; scroll scr down
	mov ah, 7
	int 10h
	jmp print_cseq

print_cseq:
	mov si, Text
	push word EndTxt
	jmp print

pchar:
	push bp
	mov bp, sp

	; set cur pos
	mov ah, 2
	int 10h
	lodsb

	; write char
	mov ah, 9
	int 10h
	inc dl

	mov sp, bp
	pop bp
	ret

print:
	pop ax
	push ax
	cmp si, ax
	je enter_pm

	call pchar

	; if scr edge
	cmp dl, 80
	jne print
	xor dl, dl
	inc dh

	; if scr bottom
	cmp dh, 25
	jne print
	xor dh, dh

	jmp enter_pm

gdt:
	; null desc
	dd 0x00000000
	dd 0x00000000

	code_desc:
	dw 0xFFFF
	dw 0
	db 0
	db 0b10011010
	db 0b11001111
	db 0

	data_desc:
	dw 0xFFFF
	dw 0
	db 0
	db 0b10010010
	db 0b11001111
	db 0

gdt_end:

gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt

enter_pm:
	; enter prot mode
	cli
	lgdt [gdt_desc]
	mov edx, cr0
	or edx, 0x00000001
	mov cr0, edx
	jmp CODE_SEG:load_kernel

load_kernel:
	; run kernel

times 0200h - 2 - ($ - $$) db 0
dw 0AA55h
; times 1474560 - ($ - $$) db 0
CODE_SEG equ code_desc - gdt
DATA_SEG equ data_desc - gdt
