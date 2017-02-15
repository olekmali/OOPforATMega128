//* OOP bios_uart0.cpp *
#include "bios_uart0.h"
#include <avr/io.h>

Uart0 Uart0::instance;

void Uart0::initialize( uint32_t baud, uint8_t stop_mode, uint8_t parity_mode )
{
    // set up baud rate
    uint32_t temp = (16000000/16)/baud-1;
    UBRR0H = (temp >> 8) & 0x0F;
    UBRR0L = (temp & 0xFF);

    // enable both sending and receiving
    UCSR0B = (1<<RXEN)|(1<<TXEN);

    // Set frame format: 8 data bits, uart_stop_mode stop bit, uart_parity_mode parity type
    UCSR0C =  (3<<UCSZ0) | ( (stop_mode & 0x01) << USBS ) | ( (parity_mode & 0x03) << UPM00 );
}

void Uart0::shutdown()
{
    UCSR0B = 0;    
}


void Uart0::put( char c )
{
    while( 0 == (UCSR0A & 1<<UDRE) ) ;
    UDR0 = c;
}

void Uart0::flush()
{
    // wait until the send buffer is empty
    while( 0 == (UCSR0A & 1<<UDRE) ) ;
}

int  Uart0::get()
{
    while( 0 == (UCSR0A & 1<<RXC) ) ;
    uint8_t status = ( UCSR0A & ((1<<FE)|(1<<DOR)|(1<<UPE)) ); 
    uint8_t received = (uint8_t) UDR0;
    if ( status!=0 ) return( -1 );
    else             return( received );
}

uint8_t Uart0::is_ready()
{
    return( (UCSR0A & 1<<RXC)!=0 );
}
