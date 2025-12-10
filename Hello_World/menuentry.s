;--------------------------------------------------------------------------
;  menuentry.s - generate menu entry for programms
;
;  Copyright (c) 2015, 2024 boert, CC BY-SA 2.0 de
;--------------------------------------------------------------------------

    .dw 0x7f7f
    .str 'HELLO'
    .db 1
    jp  init
