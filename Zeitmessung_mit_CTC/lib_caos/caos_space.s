; some functions provided by the CAOS (=monitor program)


    .include 'caos.inc'


; Ausgabe eines Leerzeichens über UP-Nr. 24H
.globl _space
_space::
    call PV1
    .db FNSPACE
    ret
