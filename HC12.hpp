/**
 *  @file HC12.hpp
 *  @author Alberto MN
 *
 *  This is a library for long-distance wireless HC-12 modules.
 */
#ifndef HC12_HPP
#define HC12_HPP
#include <Arduino.h>
#include <SoftwareSerial.h>

class HC12
{
    public:
        HC12(uint8_t RX_Pin, uint8_t TX_Pin);
        HC12(uint8_t RX_Pin, uint8_t TX_Pin, uint8_t SET_Pin);
        enum Mode
        {
            FU1 = 49,
            FU2 = 50,
            FU3 = 51
        };
        void begin(int baudrate);
        void sleep(void);
        void wakeup(void);
        void set_mode(Mode mode);
        void set_power(short power);
        void set_channel(String channel);
        void set_baudrate(unsigned int baudrate);
        void send(String message);
        String receive(unsigned int timeout, char end);

    private:
        SoftwareSerial _serial;
        uint8_t _SET_PIN;
        Mode _MODE;
        void send_AT(String command);
};

#endif