[ bits 16 ]
org 7C00h

jmp short start

Text:	db "  [ Booting in progress... ]\0"
Date:	db "  [ RTC Placeholder ]\0"
ReadError: db "Error reading from disk\0"

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
	mov ah, 0x0
	mov al, 0x3
	int 10h

print_cseq:
	xor si, si
	xor dx, dx
	mov si, Text
	call print
	mov dh, 1
	mov dl, 0
	mov si, Date
	call print
	jmp load_kernel

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
	cmp byte [si], '\0'
	je exit_print

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

exit_print:
	ret

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

load_kernel:
	; 1st floppy drive
	mov dl, DRIVE_ID
	; disk head
	mov dh, 0x0
	; cylinder
	mov ch, 0x0
	; sector
	mov cl, 0x2
	; buff addres ptr
	mov bx, KERNEL
	; read sectors from drive
	mov ah, 0x2
	; sectors count
	mov al, 20
	int 0x13
	; skip pm if error
	mov dl, DRIVE_ID
	; get last status
	mov ah, 0x1
	int 0x13
	; return code
	cmp ah, 0x0
	jne hdl_read_err

enter_pm:
	mov si, ReadError
	mov dh, 2
	mov dl, 0
	call print

	; enter prot mode
	cli
	lgdt [gdt_desc]
	mov edx, cr0
	or edx, 0x00000001
	mov cr0, edx
	jmp CODE_SEG:start_kernel

hdl_read_err:
	mov si, ReadError
	mov dh, 2
	mov dl, 0
	call print

[ bits 32 ]
start_kernel:
	jmp KERNEL

times 0200h - 2 - ($ - $$) db 0
dw 0AA55h
; times 1474560 - ($ - $$) db 0
CODE_SEG equ code_desc - gdt
DATA_SEG equ data_desc - gdt
KERNEL equ 0x1000
DRIVE_ID equ 0x0
