	.globl _putchar

_putchar::
    ld a, l
    cp a, #0x0a
    jr z,print_crlf$

    call #0xF003
    .db #0      ; UP CRT
    ret

print_crlf$:
    call #0xF003
    .db #0x2c   ; UP CRLF
    ret
