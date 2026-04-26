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



; Modulsteuerung
;   = Lesen des Modultyps (Register A < 2)
;   = Aussenden des Steuercodes (Register A ≥ 2)
; in:
;   A   - Anzahl der Parameter
;   L   - Steckplatz
;   D   - Steuerbyte
; out:
;   H   - Modultyp (Strukturbyte)
;   D   - Modulsteuerbyte
;   A   - altes Modulsteuerbyte
.globl _modu
_modu::
                ; A schon richtig
    ld e, l     ; Steckplatz sichern
    ld hl, #2
    add hl, sp
    ld d, (hl)  ; Steuerbyte holen
    ld l, e     ; Steckplatz richtig

    call PV1
    .db FNMODU

    ld  d, a
    ld  e, h

    ; fix stack
    pop hl
    inc sp
    jp (hl)
