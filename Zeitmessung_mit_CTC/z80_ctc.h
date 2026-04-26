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

#ifndef Z80_CTC_H
#define Z80_CTC_H

#include <stdint.h>     // uint8_t, uint16_t

/*
 * CTC beim KC85/4
 * Kanal    Signal  Frequenz    Nutzung         Ausgang
 * 0        h4      27 kHz      Tonhöhe rechts  K0 Sound rechts (+Piezo)
 * 1        h4      27 kHz      Tonhöhe links   K1 Sound links
 * 2        /BI     50 Hz       Tondauer        Blink
 * 3        /BI     50 Hz       Tastatur        entfällt
 */

#define CTC_INTERRUPT_VECTOR        ( 0 << 0)
#define CTC_CONTROL_WORD            ( 1 << 0)
#define CTC_SOFTWARE_RESET          ( 1 << 1)
#define CTC_TIME_CONSTANT_FOLLOW    ( 1 << 2)
#define CTC_AUTOMATIC_TRIGGER       ( 0 << 3)
#define CTC_CLK_STARTS_TIMER        ( 1 << 3)
#define CTC_FALLING_EDGE            ( 0 << 4)
#define CTC_RISING_EDGE             ( 1 << 4)
#define CTC_PRESCALER_16            ( 0 << 5)
#define CTC_PRESCALER_256           ( 1 << 5)
#define CTC_TIMER_MODE              ( 0 << 6)
#define CTC_COUNTER_MODE            ( 1 << 6)
#define CTC_INTERRUPT_ENABLE        0x80 //( 1 << 7) //avoid warning

void setup_ctc_for_measure( void);
void setup_ctc_for_interrupt( uint8_t value);
void ctc_restore( void);
void wait_20ms( uint8_t ticks);

#endif // Z80_CTC_H
