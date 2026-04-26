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



; Tasteneingabe mit Einblendung des Cursors, 
; wartet, bis Taste gedrückt bzw. liefert die 
; Codefolge von vorher betätigter F-Taste
; in:
;   nix
; out:
;   Register A - Zeichencode (ASCII)
.globl _kbd
_kbd::
    call PV1
    .db FNKBD
    ret
