//* OOP bios_key4.c *
#include "bios_key4.h"
#include <avr/io.h>

uint8_t MenuKeys::use_count = 0;

MenuKeys::MenuKeys (void)
{
    if (use_count==0)
    {
        // set upper nibble pins on PORTE for input
        DDRE  &= 0x0F;
        // and activate pull up resistors on them
        PORTE |= 0xF0;
        // do not touch the lower nibble (to prevent interaction with any other potential libraries        
    }
    ++use_count;
}

MenuKeys::~MenuKeys (void)
{
    --use_count;
    if (use_count==0)
    {
        // to be safe and low power set the upper nibble back to input and shut off pull up resistors
        DDRE &= 0x0F;
        PORTE&= 0x0F;
    }         
}

uint8_t MenuKeys::get (void) const
{
    return( ((uint8_t)(~PINE))>>4 );
        //   ^^^^^^^^   typecasting to make sure that this >> is done on an unsigned data type
        //              so that 0s are introduced to the left and & 0x0F step can be skipped
}
