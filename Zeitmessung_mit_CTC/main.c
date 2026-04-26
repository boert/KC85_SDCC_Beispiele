/*-------------------------------------------------------------------------
   Copyright (C) 2026, Bert Lange

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library; see the file COPYING. If not, write to the
   Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
    MA 02110-1301, USA.

   As a special exception, if you link this library with other files,
   some of which are compiled with SDCC, to produce an executable,
   this library does not by itself cause the resulting executable to
   be covered by the GNU General Public License. This exception does
   not however invalidate any other reasons why the executable file
    might be covered by the GNU General Public License.
--------------------------------------------------------------------------*/

#include <stdint.h>     // uint8_t, uint16_t
#include <stdio.h>      // printf
#include "z80_ctc.h"    // setup_ctc_for_interrupt
#include "caos.h"       // CTC2


uint16_t wurzel( uint32_t value)
{
    uint16_t sub;
    uint16_t result;

    result = 0;
    sub = 1;
    while( value >= sub)
    {
        result++;
        value = value - sub;
        sub = sub + 2;
    }
    return result;
}


//////////////////////////////
// Hauptprogramm
void main( void)
{
    uint8_t  time_start;
    uint8_t  time_end;
    uint16_t time;
    uint16_t value;

    printf( "\nZeitmessung mit CTC, Kanal 2\n");
    setup_ctc_for_measure();

    time_start = CTC2;
    value = wurzel( 1000000);
    time_end = CTC2;

    printf( "Ergebnis der Berechnung: %u\n", value);

    time = time_start - time_end;
    time = time * 20; // jetzt in Millisekunden
    printf( "Laufzeit der Berechnung: %u ms\n", time);
}
