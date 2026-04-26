; some functions provided by the CAOS (=monitor program)


    .include 'caos.inc'

; Sprung auf RESET (Warmstart des Systems)
.globl _bye
_bye::
    call PV1
    .db FNBYE
