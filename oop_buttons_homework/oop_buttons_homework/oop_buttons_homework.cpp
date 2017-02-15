/*
 * OOP Case study: test file for Homework 8 button classes
 *
 * Created: 10/15/2015 1:00:00 AM
 *  Author: Aleksander Malinowski
 */ 

#include "bios_key4.h"
#include "bios_led8.h"

#include "lib_buttons.h"


int main(void)
{
    // INITIALIZATION
    MenuKeys Keys;
    LEDs     disp;

    DebouncedTogglePushButton    buttons[4];
    static const uint8_t   keymask[4] = {  MenuKeys::Key4, MenuKeys::Key5, MenuKeys::Key6, MenuKeys::Key7  };
    static const uint8_t   ledmask[4] = {  LEDs::LED0,     LEDs::LED1,     LEDs::LED2,     LEDs::LED3      };

    uint16_t cnt = 0;
    // MAIN SUPERLOOP
    while(1)
    {
        for (uint8_t i=0; i<4; ++i) {
            buttons[i].update( 0!= (Keys.get() & keymask[i]) );
            if ( buttons[i].getState() )  disp.set( disp.get() | ledmask[i] );
            else                          disp.set( disp.get() & ~(ledmask[i]) );
        }

        if (0==cnt) {
            cnt=16384;
            disp.set( disp.get() ^ 0x80);
        } else cnt--;
    }

    return(0);
}
