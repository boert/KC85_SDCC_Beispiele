;                        __sdcccall(0)  new
; first parameter LSB -> SP+2           A
; first parameter MSB -> SP+3
; 2nd   parameter LSB -> SP+4           H
; 2nd   parameter MSB -> SP+5           L
; 3rd   parameter LSB -> SP+6           SP+3
; 3rd   parameter MSB -> SP+7
; return values on A (8bit) or DE (16 bit)

; read IO port HL
; output value on A
.globl _in16
_in16::
    push bc
    ld  b, h
    ld  c, l
    in  a, (c)
    pop bc
    ret
