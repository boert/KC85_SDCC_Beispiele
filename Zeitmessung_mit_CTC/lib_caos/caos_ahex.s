; some functions provided by the CAOS (=monitor program)

;                        __sdcccall(0)  new
; first parameter LSB -> SP+2           A
; first parameter MSB -> SP+3
; 2nd   parameter LSB -> SP+4           L
; 2nd   parameter MSB -> SP+5           H
; 3rd   parameter LSB -> SP+6           SP+2
; 3rd   parameter MSB -> SP+7
; return values on A (8bit) or DE (16 bit)
; return values on L or HL (old)

    .include 'caos.inc'



; Ausgabe Register A als Hexzahl
; in:
;  Register A 
.globl _ahex
_ahex::

    call PV1
    .db FNAHEX
    ret
