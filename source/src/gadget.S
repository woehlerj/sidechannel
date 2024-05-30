.global FUN1
FUN1:
    POP %RDX
    ret

.global FUN2
FUN2:
    POP %RSI
    POP %R15
    ret

.global FUN3
FUN3:
    POP %RDI
    ret

.global FUN4
FUN4:
    MOV %RAX, %RDI
    ret
