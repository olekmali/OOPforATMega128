//* OOP bios_led8.c *
#include "bios_led8.h"
#include <avr/io.h>

uint8_t LEDs::use_count = 0;

LEDs::LEDs (void)
{
    if (use_count==0)
    {
        // set all pins on PORTA for output
        DDRA  = 0xFF;   // 0b11111111
    }
    ++use_count;
}

LEDs::~LEDs (void)
{
    --use_count;
    if (use_count==0)
    {
        // to be safe and low power set the upper nibble back to input and shut off pull up resistors
        DDRA = 0;
        PINA = 0;
    }
}

uint8_t LEDs::get (void) const
{
    // no need for delay after writing to PORTA 
    // as it takes time to call the function
    return( PINA );
}

void LEDs::set ( uint8_t val )
{
    PORTA = val;
}
