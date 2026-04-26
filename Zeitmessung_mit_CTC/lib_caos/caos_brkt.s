; some functions provided by the CAOS (=monitor program)

;                        __sdcccall(0)  new
; first parameter LSB -> SP+2           A
; first parameter MSB -> SP+3
; 2nd   parameter LSB -> SP+4           H
; 2nd   parameter MSB -> SP+5           L
; 3rd   parameter LSB -> SP+6           SP+3
; 3rd   parameter MSB -> SP+7
; return values on A (8bit) or DE (16 bit)

    .include 'caos.inc'



; Test auf Unterbrechungsanforderung
; out:
;  Register A - Zeichencode (ASCII)
;  Register F - CY = 1, Taste BRK gedrückt
.globl _brkt
_brkt::
    call PV1
    .db FNBRKT

    ld d, a

    ;ld  a, 0x01
    .db 0x3e
    .db 0x01
    and e
    ld  e, a

    ret
