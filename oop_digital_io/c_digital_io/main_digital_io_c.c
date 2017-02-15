//* Simple Digital IO test set in plain C *
#include "bios_key4c.h"
#include "bios_led8c.h"

#include <stdint.h>

# define F_CPU 16000000UL
#include <util/delay.h>


uint8_t choose_on_power_on(uint8_t wait) {
    uint8_t     result=0;
    do {
        result = key4_get();
    } while ( wait && (0==result) );

    if (0!=result) {
        uint8_t waitst=0;
        while ( waitst<64 ) {
            if ( 0 != key4_get() ) waitst=0;
            else waitst++;
        }
    }
    return(result);
}



void main_toggle1() {
	uint8_t  state = 0;
	
	// MAIN SUPERLOOP
	while(1)
	{
    	uint8_t current = key4_get();
        uint8_t change  = current ^ state;
        state = current;
    	    if ( (0 != (change & B_K4)) && (0 != (current & B_K4)) ) led8_set( led8_get() ^ B_L0 );
    	    if ( (0 != (change & B_K5)) && (0 != (current & B_K5)) ) led8_set( led8_get() ^ B_L1 );
    	    if ( (0 != (change & B_K6)) && (0 != (current & B_K6)) ) led8_set( led8_get() ^ B_L2 );
    	    if ( (0 != (change & B_K7)) && (0 != (current & B_K7)) ) led8_set( led8_get() ^ B_L3 );

        // let's do at least lousy debouncing
        _delay_ms(10); // from <util/delay.h>
    }
}



void main_menu1() {
	uint8_t  state = 0;
    uint8_t  mode  = 1;
    uint8_t  prev  = 0;
	
	// MAIN SUPERLOOP
	while(1)
	{
    	uint8_t current = key4_get();
    	uint8_t change  = current ^ state;
    	state = current;
    	if ( (0 != (change & B_K4)) && (0 != (current & B_K4)) ) { if (0x01<mode) mode=mode>>1; }
    	if ( (0 != (change & B_K5)) && (0 != (current & B_K5)) ) {}
    	if ( (0 != (change & B_K6)) && (0 != (current & B_K6)) ) {}
    	if ( (0 != (change & B_K7)) && (0 != (current & B_K7)) ) { if (0x08>mode) mode=mode<<1; }

        if (mode!=prev) {
            led8_set( led8_get() ^ mode ^ prev );
            prev = mode;            
        }

    	// let's do at least lousy debouncing
    	_delay_ms(10); // from <util/delay.h>
	}
}


void main_blank1() {
    while (1) ;
}


void main_blank2() {
    while (1) ;
}


int main(void)
{
    // INITIALIZATION
    led8_init();
    key4_init();

    switch ( choose_on_power_on(1) ) {
    case B_K4 :
        led8_set(B_L5);
        main_toggle1();
        break;
    case B_K5 :
        led8_set(B_L5|B_L6);
        main_menu1();
        break;
    case B_K6 :
        led8_set(B_L5|B_L7);
        main_blank1();
        break;
    case B_K7 : 
        led8_set(B_L5|B_L6|B_L7);
        main_blank2();
        break;
    }

	return(0);
}
