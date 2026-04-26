; some functions provided by the CAOS (=monitor program)

    .include 'caos.inc'

; Ausschrift des Textes „ERROR“
.globl _errm
_errm::
    call PV1
    .db FNERRM
    ret
