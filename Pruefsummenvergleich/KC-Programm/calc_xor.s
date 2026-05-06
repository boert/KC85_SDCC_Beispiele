; sdcccall(1)
; Parameters 16 bit + 16 bit
; HL + DE
;
; return 8 bit
; A


;;
;; Input:
;;  HL = Data address
;;  DE = Data length
;;
;; Output:
;;  A  = XOR
;;  HL,BC,AF are modified

.globl _calc_xor_asm
_calc_xor_asm::

    ; init A
    xor a

    ; prepare fast loop
    ; https://map.grauw.nl/articles/fast_loops.php
    ; Number of loops is in DE
    ld  b, e
    dec de
    inc d

loop:
    xor a, (hl)
    inc hl          ; naechste Adresse

    jr nc, skip_inc
    inc c

skip_inc:
    djnz loop       ; loop counter
    dec d
    jr  nz, loop

    ret
