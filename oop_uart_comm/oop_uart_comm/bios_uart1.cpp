//* OOP bios_uart1.cpp *
#include "bios_uart1.h"
#include <avr/io.h>

Uart1 Uart1::instance;

void Uart1::initialize( uint32_t baud, uint8_t stop_mode, uint8_t parity_mode )
{
    // set up baud rate
    uint32_t temp = (16000000/16)/baud-1;
    UBRR1H = (temp >> 8) & 0x0F;
    UBRR1L = (temp & 0xFF);

    // enable both sending and receiving
    UCSR1B = (1<<RXEN)|(1<<TXEN);

    // Set frame format: 8 data bits, uart_stop_mode stop bit, uart_parity_mode parity type
    UCSR1C =  (3<<UCSZ0) | ( (stop_mode & 0x01) << USBS ) | ( (parity_mode & 0x03) << UPM10 );
}

void Uart1::shutdown()
{
    UCSR1B = 0;    
}


void Uart1::put( char c )
{
    while( 0 == (UCSR1A & 1<<UDRE) ) ;
    UDR1 = c;
}

void Uart1::flush()
{
    // wait until the send buffer is empty
    while( 0 == (UCSR1A & 1<<UDRE) ) ;
}

int  Uart1::get()
{
    while( 0 == (UCSR1A & 1<<RXC) ) ;
    uint8_t status = ( UCSR1A & ((1<<FE)|(1<<DOR)|(1<<UPE)) ); 
    uint8_t received = (uint8_t) UDR1;
    if ( status!=0 ) return( -1 );
    else             return( received );    
}

uint8_t Uart1::is_ready()
{
    return( (UCSR1A & 1<<RXC)!=0 );
}
