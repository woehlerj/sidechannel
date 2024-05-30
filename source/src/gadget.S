.global FUN1
FUN1:
    SYSCALL
    ret

.global FUN2
FUN2:
    POP %RAX
    ret
