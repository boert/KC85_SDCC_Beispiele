; some functions provided by the CAOS (=monitor program)

    .include 'caos.inc'


; Komplementiere Cursor
.globl _cucp
_cucp::
    call PV1
    .db FNCUCP
    ret
