//* OOP bios_uart1.h *
#ifndef UART1_H_
#define UART1_H_

#include "lib_com_abase.h"

class Uart1 : public com_abase {
public:
    static Uart1& getInstance() { return(instance); }

    void initialize( uint32_t baud, uint8_t stop_mode, uint8_t  parity_mode );
    void shutdown();

    void put( char c );
    void flush();
    int  get();
    uint8_t is_ready();

private:
    static Uart1 instance;
    Uart1() {}
    Uart1(const Uart1&);
    void operator=(const Uart1&);
};

#endif /* UART1_H_ */
