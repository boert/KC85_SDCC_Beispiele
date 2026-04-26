; some functions provided by the CAOS (=monitor program)

    .include 'caos.inc'


; Ausgabe von „NEWLINE“ (Codes 0DH=CR und 0AH=LF)
.globl _crlf
_crlf::
    call PV1
    .db FNCRLF
    ret
