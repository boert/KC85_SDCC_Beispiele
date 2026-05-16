#include <stdint.h>     // uint16_t
#include <stdio.h>      // printf
#include <string.h>     // memmove, memcpy, memcmp
#include <stdbool.h>    // bool, true, false
#include "caos.h"       // home, cstbt, modu
#include "z80_ctc.h"    // setup_ctc_for_measure


//////////////////////////////
// defines
#define IRM_ARGN        *(volatile uint8_t*)  0xB781
#define IRM_ARG1        *(volatile uint16_t*) 0xB782
#define IRM_ARG2        *(volatile uint16_t*) 0xB784
#define IRM_ARG3        *(volatile uint16_t*) 0xB786


//////////////////////////////
// globale Variablen


//////////////////////////////
// ISR stuff (timer)
typedef void (*isrptr)( void);
#define CTC2_VECTOR     *(isrptr*) 0x01EC
volatile uint16_t time;
isrptr ctc2_vector_save;


//////////////////////////////
// Prototypes
void timer_isr( void) __critical __interrupt( 0) __naked;

uint16_t calc_crc16( uint8_t* address, uint16_t length);
uint16_t calc_adler16( uint8_t* address, uint16_t length);
uint16_t calc_fsum_255( uint8_t* data, uint16_t length);
uint16_t calc_fsum_256( uint8_t* data, uint16_t length);
uint16_t calc_fsum_kc( uint8_t* addr, uint16_t length);
uint16_t calc_sum16( uint8_t* address, uint16_t length);
uint8_t  calc_xor( uint8_t* address, uint16_t length);

extern uint16_t calc_crc16_asm( uint8_t* data, uint16_t len);
extern uint16_t calc_adler16_asm( uint8_t* data, uint16_t len);
extern uint16_t calc_fletcher_255_asm( uint8_t* data, uint16_t len);
extern uint16_t calc_fletcher_256_asm( uint8_t* data, uint16_t len);
extern uint16_t calc_fletcher_kc_asm( uint8_t* data, uint16_t len);
extern uint16_t calc_sum16_asm( uint8_t* data, uint16_t len);
extern uint8_t  calc_xor_asm( uint8_t* data, uint16_t len);


//////////////////////////////
// Textersetzung
#define ae "\x7b"
#define oe "\x7c"
#define ue "\x7d"
#define sz "\x7e"
#define CLL "\x02"



//////////////////////////////
// Hauptprogramm
void main( void)
{
    printf( CLL "compiled: " __TIMESTAMP__"\n");
    printf( CLL "Pr"ue"fsummen "ue"ber 8k Speicher\n");

    if( IRM_ARGN > 0)
    {
        // entweder Speicher füllen
        uint8_t fill = IRM_ARG1;
        printf( CLL "Speicher f"ue"llen (%02Xh)\n", fill);
        memset( (uint8_t*)0x4000, fill, 8192);
    }
    else
    {
        // oder nicht antasten
        printf( CLL "Speicher 4000..5FFFh\n");
    }

    // Zeitmessungen vorbereiten
    ctc2_vector_save = CTC2_VECTOR;
    CTC2_VECTOR = timer_isr;
    #define TIME_FACTOR 20
    setup_ctc_for_interrupt( TIME_FACTOR/20); // 20 ms = 50 Hz

    uint16_t runtime;
    uint16_t csum;
    uint8_t  bsum;


    printf( CLL "C-Routinen\n");
    printf( CLL "crc16         ");
    time = 0;
    csum = calc_crc16( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "Adler-16      ");
    time = 0;
    csum = calc_adler16( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "fletcher 255  ");
    time = 0;
    csum = calc_fsum_255( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "fletcher 256  ");
    time = 0;
    csum = calc_fsum_256( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "fletcher KC   ");
    time = 0;
    csum = calc_fsum_kc( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "sum16         ");
    time = 0;
    csum = calc_sum16( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "xor           ");
    time = 0;
    bsum = calc_xor( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "  %02X (%4d ms)\n", bsum, runtime * TIME_FACTOR);


    printf( CLL "ASM-Routinen\n");
    printf( CLL "crc16         ");
    time = 0;
    csum = calc_crc16_asm( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "Adler-16      ");
    time = 0;
    csum = calc_adler16_asm( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "fletcher 255  ");
    time = 0;
    csum = calc_fletcher_255_asm( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "fletcher 256  ");
    time = 0;
    csum = calc_fletcher_256_asm( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "fletcher KC   ");
    time = 0;
    csum = calc_fletcher_kc_asm( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "sum16         ");
    time = 0;
    csum = calc_sum16_asm( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "%04X (%4d ms)\n", csum, runtime * TIME_FACTOR);

    printf( CLL "xor           ");
    time = 0;
    bsum = calc_xor_asm( (uint8_t*) 0x4000, 8192);
    runtime = time;
    printf( "  %02X (%4d ms)\n", bsum, runtime * TIME_FACTOR);


    // Zeitmessung nachbereiten
    ctc_restore();
    CTC2_VECTOR = ctc2_vector_save;
}


////////////////////////////////////////
// Hilfsfunktionen

// __critical     no EI at the beginning
// __interrupt(n) for maskable interrupts
// __naked        no push and pop (else sdcc will save all regs)
void timer_isr( void) __critical __interrupt( 0) __naked
{
    __asm
        push bc
    __endasm;
    time++;
    __asm
        pop bc
        ei
        reti
    __endasm;
}


uint8_t calc_xor( uint8_t* address, uint16_t length)
{
    uint8_t value = 0;
    for( uint16_t index = 0; index < length; index++)
    {
        value ^= *address;
        address++;
    }
    return value;
}


uint16_t calc_sum16( uint8_t* address, uint16_t length)
{
    uint16_t value = 0;
    for( uint16_t index = 0; index < length; index++)
    {
        value += *address;
        address++;
    }
    return value;
}


uint16_t calc_fsum_kc( uint8_t* data, uint16_t length)
{
    uint16_t index;
    uint8_t a;
    uint8_t b;

    a = data[ 0];
    b = 0;

    for( index = 0; index < length; index++)
    {
        a += data[ index];
        b += a;
    }
    return ((uint16_t) b << 8) | a;
}


uint16_t calc_fsum_256( uint8_t* data, uint16_t length)
{
    uint16_t index;
    uint8_t a;
    uint8_t b;

    a = 0;
    b = 0;

    for( index = 0; index < length; index++)
    {
        a += data[ index];
        b += a;
    }
    return ((uint16_t) b << 8) | a;
}


uint16_t calc_fsum_255( uint8_t* data, uint16_t length)
{
    uint16_t index;
    uint16_t a;
    uint16_t b;

    a = 0;
    b = 0;

    for( index = 0; index < length; index++)
    {
        a = (a + data[ index]) % 255;
        b = (b + a) % 255;
    }
    return ((uint16_t) b << 8) | a;
}


// crc16
// https://mdfs.net/Info/Comp/Comms/CRC16.htm
#define poly 0x1021
uint16_t xmodem_crc16( uint8_t byte, uint16_t crc)
{
    crc = crc ^ (byte << 8);
    for (int i=0; i<8; i++)
    {
        if (crc & 0x8000)
        {
            crc = crc << 1;
            crc = (crc ^ poly) & 0xFFFF;
        }
        else
        {
            crc = crc << 1;
        }
    }
    return crc;
}
uint16_t calc_crc16( uint8_t* data, uint16_t length)
{
    uint16_t index;
    uint16_t crc;

    crc = 0xffff;
    for( index = 0; index < length; index++)
    {
        crc = xmodem_crc16( data[ index], crc);
    }
    return crc;
}

uint16_t calc_adler16( uint8_t* data, uint16_t length)
{
    uint16_t index;
    uint16_t a;
    uint16_t b;

    a = 1;
    b = 0;

    for( index = 0; index < length; index++)
    {
        a = a + data[ index];
        while( a >= 251)
        {
            a -= 251;
        }
        b = b + a;
        while( b >= 251)
        {
            b -= 251;
        }
    }
    return ((uint16_t) b << 8) | a;
}
