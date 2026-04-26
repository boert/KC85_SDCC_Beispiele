; some functions provided by the CAOS (=monitor program)

;                        old    new
; first parameter LSB -> SP+2   A
; first parameter MSB -> SP+3
; 2nd   parameter LSB -> SP+4   H
; 2nd   parameter MSB -> SP+5   L
; 3rd   parameter LSB -> SP+6   SP+3
; 3rd   parameter MSB -> SP+7
; return values on A (8bit) or DE (16 bit)

    .include 'caos.inc'



; Farbe einstellen
; in:
;  ARGN - Anzahl der Argumente
;  L    - Vordergrundfarbe
;  E    - Hintergrundfarbe
.globl _colorup
_colorup::

    ; bring parameters to correct mem/registers
    ld  (#ARGN), a
    push hl     ; save L
    ld hl, #6
    add hl, sp
    ld	e, (hl)
    pop hl      ; restore L

    ; make system call
    call PV1
    .db FNCOLORUP

    ; fix stack
    pop hl
    inc sp
    jp (hl)
    ;ret
