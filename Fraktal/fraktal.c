#include <stdint.h>     // uint8_t, uint16_t
#include <stdio.h>      // printf
#include "caos.h"
#include "z80_ctc.h"    // setup_ctc_for_interrupt

#define IRM_COLOR       *(volatile uint8_t*)  0xB7A3
typedef void (*isrptr)( void);
#define CTC2_VECTOR     *(isrptr*) 0x01EC

void textforeground( uint8_t fg_color);
void textbackground( uint8_t bg_color);

volatile uint16_t time;
isrptr ctc2_vector_save;

// max. 21 minutes
// max. 1310 seconds
// resolution: seconds
void timer_isr( void) __interrupt( 0)
{
    time++;
}


void main( void)
{
    uint8_t px, py;
    float xz, yz, xt, m;
    float x, y;
    uint8_t i;

    textbackground( BLUE);
    crt( CLS);

    time = 0;
    ctc2_vector_save = CTC2_VECTOR;
    CTC2_VECTOR = timer_isr;
    setup_ctc_for_interrupt( 50);

    for( py = 0; py < 22; ++py)
    {
        for( px = 0; px < 31; ++px)
        {
            xz = px * 3.5 / 32 - 2.5;
            yz = py * 2.0 / 22 - 1.0;
            x = 0;
            y = 0;
            i = 0;
            while(( i < 15) && (( x*x + y*y) < 4.0))
            {
                xt = x * x - y * y + xz;
                m = x * y;
                y = m + m + yz;
                x = xt;
                i++;
            }
            textforeground( i);
            crt( 219);
        }
        crlf();
    }
    ctc_restore();
    CTC2_VECTOR = ctc2_vector_save;
    textforeground( 7);
    printf( "%d s\n", time);
}


void textforeground( uint8_t fg_color)
{
    uint8_t col;

    col = IRM_COLOR;
    col = col & 0x07;
    col = col | (fg_color << 3);
    IRM_COLOR = col;
}

void textbackground( uint8_t bg_color)
{
    uint8_t col;

    col = IRM_COLOR;
    col = col & 0xF8;
    col = col | bg_color;
    IRM_COLOR = col;
}
