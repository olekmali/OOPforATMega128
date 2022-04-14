//* OOP bios_led8.h *
#ifndef BIOS_LED8_H_
#define BIOS_LED8_H_
#include <stdint.h>

class LEDs {
public:
const static uint8_t LED7 = 0x80;
const static uint8_t LED6 = 0x40;
const static uint8_t LED5 = 0x20;
const static uint8_t LED4 = 0x10;
const static uint8_t LED3 = 0x08;
const static uint8_t LED2 = 0x04;
const static uint8_t LED1 = 0x02;
const static uint8_t LED0 = 0x01;

public:
LEDs();
~LEDs();
uint8_t get() const;
void    set(uint8_t val);

private:
LEDs(const LEDs&);              // no passing by value please
void operator=(const LEDs&);    // no reassignment

private:
static uint8_t use_count;       // in case multiple instances are declared
};

#endif /* BIOS_LED8_H_ */