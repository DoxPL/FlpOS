; call kernel after
; enabling pmode
[bits 32]
[extern main]
call main
jmp $
