/**
 *  @file HC-12.hpp
 *  @author Alberto MN
 *
 *  This is a library for long-distance wireless HC-12 modules.
 */
#ifndef HC12_HPP
#define HC12_HPP
#include <Arduino.h>
#include <SoftwareSerial.h>

#define AT_DELAY 100

class HC12
{
    private:
        SoftwareSerial _serial;
        uint8_t _SET_PIN;

    public:
        HC12(uint8_t RX_Pin, uint8_t TX_Pin);
        HC12(uint8_t RX_Pin, uint8_t TX_Pin, uint8_t SET_Pin);
        enum Mode
        {
            FU1 = 49,
            FU2 = 50,
            FU3 = 51
        };
        void begin(void);
        void sleep(void);
        void wakeup(void);
        void setup_mode(Mode mode);
        void setup_power(short power);
};

#endif