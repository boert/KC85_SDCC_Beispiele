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

#include "caos.h"       // CTC2
#include "z80_ctc.h"



// -------------------------------
// CTC Kanal 2 auf Zählmodus, Startwert 256
void setup_ctc_for_measure( void)
{
    // setup CTC with count value 256
    CTC2 =
        CTC_CONTROL_WORD |
        CTC_SOFTWARE_RESET |
        CTC_TIME_CONSTANT_FOLLOW |
        CTC_COUNTER_MODE;
    CTC2 = 0xff;
}


// -------------------------------
// CTC Kanal 2 auf Zählmodus, Start mit value
void setup_ctc_for_interrupt( uint8_t value)
{
    CTC2 =
        CTC_CONTROL_WORD |
        CTC_SOFTWARE_RESET |
        CTC_TIME_CONSTANT_FOLLOW |
        CTC_COUNTER_MODE |
        CTC_INTERRUPT_ENABLE;
    CTC2 = value;
}


void ctc_restore( void)
{
    // restore defaults
    CTC2 =
        CTC_CONTROL_WORD +
        CTC_SOFTWARE_RESET +
        CTC_TIME_CONSTANT_FOLLOW +
        CTC_COUNTER_MODE;
    CTC2 = 12;      // Zeitkonstante
}


// -------------------------------
// 1 tick = 20 ms
void wait_20ms( uint8_t ticks)
{
    uint8_t end;

    setup_ctc_for_measure();
    end   = CTC2 - ticks;
    while( CTC2 > end) {};
}
