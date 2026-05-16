;; Quelle:
;; https://github.com/RobTillaart/Adler

; sdcccall(1)
; Parameters 16 bit + 16 bit
; HL + DE
;
; return 16 bit
; DE


;; Adler-16 checksum, mod 251, a = 1, b = 0
;;
;; Input:
;;  HL = Data address
;;  BC = Data length
;;
;; Output:
;;  DE = Adler-16
;;  HL,BC,AF are modified

.globl _calc_adler16_asm
_calc_adler16_asm::
    ; resort parameters
    ld b, d
    ld c, e
adler16:
    ; Initialize both sums
    ld de, #0001 ; sum 2, sum 1

    ; Adjust 16-bit length for 2x8-bit loops
    inc b
    dec bc
    inc c
_adler16_loop:
      ld a, (hl)
      inc hl

      ; sum1 += data
      add a, e
      jr nc, test1
      sub a, #251
      cp #251
      jr c, _nomod1
      sub a, #251
test1:
      cp #251
      jr c, _nomod1
      sub a, #251
_nomod1:
      ld e, a

      ; sum2 += sum1
      add a, d
      jr nc, test2
      sub a, #251
      cp #251
      jr c, _nomod2    ; C=1 --> overflow
      sub a, #251
test2:
      cp #251
      jr c, _nomod2     ; C=1 --> less than A
      sub a, #251
_nomod2:
      ld d, a
      dec c
     jr nz,_adler16_loop
    djnz   _adler16_loop

    ret

