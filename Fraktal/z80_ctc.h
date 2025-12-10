#ifndef Z80_CTC_H
#define Z80_CTC_H

#include <stdint.h>     // uint8_t, uint16_t

/*
 * CTC beim KC85/4
 * Kanal    Signal  Frequenz    Ausgang
 * 0        h4      27 kHz      K0 Sound rechts (+Piezo)
 * 1        h4      27 kHz      K1 Sound links
 * 2        /BI     50 Hz       Blink
 * 3        /BI     50 Hz       entfällt
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
