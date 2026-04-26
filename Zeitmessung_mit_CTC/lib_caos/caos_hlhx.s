; some functions provided by the CAOS (=monitor program)

;                        __sdcccall(0)  new
; first parameter LSB -> SP+2           H
; first parameter MSB -> SP+3           L
; return values on A (8bit) or DE (16 bit)
; return values on L or HL (old)

    .include 'caos.inc'



; Ausgabe des Wertes des Registers HL als Hexzahl
; und danach ein Leerzeichen
; in:
;  Register HL
.globl _hlhx
_hlhx::
    call PV1
    .db FNHLHX
    ret
    ; TODO: check stack

