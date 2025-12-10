#include "caos.h"       // CTC2
#include "z80_ctc.h"



// -------------------------------
// CTC Kanal 2 auf Zählmodus, Start mit 256
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
