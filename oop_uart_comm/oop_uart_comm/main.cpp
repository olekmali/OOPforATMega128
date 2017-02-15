/*
 * OOP Case study: oop_uart_comm
 *
 * Created: 12/1/2013 3:52:02 PM
 *  Author: Aleksander Malinowski
 */ 


#include "bios_key4.h"
#include "bios_led8.h"
#include "bios_uart0.h"
#include "bios_uart1.h"
#include "lib_com.h"
#include <stdlib.h>

uint8_t count_bits(uint8_t byte)
{
    uint8_t result=0;
    while ( byte != 0 )
    {
        if ( (byte & 0x01) != 0 ) ++result;
        byte = byte >> 1;
    }
    return(result);
}


int main(void)
{
    // INITIALIZATION
    MenuKeys K;
    LEDs     L;

    Uart1    &com1 = Uart1::getInstance();
    com1.initialize(com_abase::uart_bps_9600, com_abase::uart_stop_two, com_abase::uart_parity_none);
    comlink  datalink( &com1 );

    Uart0    &com0 = Uart0::getInstance();
    com0.initialize(com_abase::uart_bps_57600, com_abase::uart_stop_two, com_abase::uart_parity_none);
    textlink debuglink( &com0 );    

    // MAIN SUPERLOOP
    while(1)
    {
        uint8_t local, remote = 0;
        char buffer[5];
        
        local = K.get();
        datalink.put( local );
        if ( datalink.is_ready() ) 
            remote = datalink.get();
        L.set( remote | local<<4 );
        
        itoa( count_bits(local) + count_bits(remote), buffer, 10);
        debuglink.puts(buffer);
        debuglink.puts("\n\r");
    }

    return(0);
}