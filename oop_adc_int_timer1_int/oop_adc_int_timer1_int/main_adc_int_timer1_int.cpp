/*
 * OOP Case study: oop_adc_int_timer1_int
 *
 * Created: 11/1/2014 3:52:02 PM
 *  Author: Aleksander Malinowski
 */ 

#include "lib_atomic.h"
#include "bios_key4.h"
#include "bios_led8.h"
#include "bios_timer1.h"
#include "bios_adc.h"

#include <stdlib.h>
#include <avr/interrupt.h>

class myInterrupt : public int_abase {
public:
    virtual void    handle();
    myInterrupt() : counter(0) {}    
private:
    uint8_t counter;
};


void myInterrupt::handle() {
    // You are inside interrupt
    // Avoid:
    //  loops with undetermined delay 
    //  or anything computationally intense
    //      including use of integer * and /
    //  not to mention anything floating point
    if (counter==0)
    {
        counter = 10;
        // HERE do things every so many interrupts
        ADConverter::getInstance().startRound();
    } else {
        counter--;
    }
}


int main(void)
{
    // INITIALIZATION
    MenuKeys Keys;
    LEDs     LEDs;
    
    myInterrupt myInt;
    
    //Timer1   &T1 = Timer1::getInstance();
    //T1.initialize(1000, &myInt, Timer1::timer_prescale_1);
    Timer1::getInstance().initialize(1000, &myInt, Timer1::timer_prescale_1);

    ADConverter &V1 = ADConverter::getInstance();
    V1.initialize();

    sei();
    // MAIN SUPERLOOP
    while(1)
    {
        while ( !V1.isReady() ) ;
        V1.resetReady();
        
        if (Keys.get() & MenuKeys::Key7)
            LEDs.set(V1.getRecent(0));
        else
            LEDs.set(V1.getRecent(1));
    }

    return(0);
}
