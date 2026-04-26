; some functions provided by the CAOS (=monitor program)

    .include 'caos.inc'

; Rückgabe der Steuerung an CAOS ohne Speicherinitialisierung
.globl _loop
_loop::
    call PV1
    .db FNLOOP
