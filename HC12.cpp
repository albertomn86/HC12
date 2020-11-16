#include "HC12.hpp"

unsigned long AT_DELAY = 100;

/**
 * @brief Construct a new HC12 object.
 *
 * @param RX_Pin RXD pin on HC12 module.
 * @param TX_Pin TXD pin on HC12 module.
 */
HC12::HC12(uint8_t RX_Pin, uint8_t TX_Pin): _serial(SoftwareSerial(RX_Pin, TX_Pin))
{
    _SET_PIN = 0;
    _MODE = FU3;
}


/**
 * @brief Construct a new HC12 object.
 *
 * @param RX_Pin RXD pin on HC12 module.
 * @param TX_Pin TXD pin on HC12 module.
 * @param SET_Pin SET pin on HC12 module.
 */
HC12::HC12(uint8_t RX_Pin, uint8_t TX_Pin, uint8_t SET_Pin): _serial(SoftwareSerial(RX_Pin, TX_Pin))
{
    _SET_PIN = SET_Pin;
    _MODE = FU3;
}


/**
 * @brief Initialize the communication with the HC12 module.
 */
void HC12::begin(int baudrate)
{
    _serial.begin(baudrate);
    if (_SET_PIN > 0)
    {
        digitalWrite(_SET_PIN, HIGH);
    }
    delay(AT_DELAY);
}


/**
 * @brief Sleep mode.
 *
 */
void HC12::sleep(void)
{
    if (_SET_PIN == 0) return;
    digitalWrite(_SET_PIN, LOW);
    delay(AT_DELAY);
    // Send command
    _serial.print("AT+SLEEP");
    delay(AT_DELAY);
    // Read response
    while(_serial.available() > 0)
    {
        char c = _serial.read();
    }
    digitalWrite(_SET_PIN, HIGH);
    delay(AT_DELAY);
}


/**
 * @brief Wake Up.
 *
 */
void HC12::wakeup(void)
{
    if (_SET_PIN == 0) return;
    digitalWrite(_SET_PIN, LOW);
    delay(AT_DELAY);
    // Send command
    _serial.print("AT");
    delay(AT_DELAY);
    // Read response
    while(_serial.available() > 0)
    {
        char c = _serial.read();
    }
    digitalWrite(_SET_PIN, HIGH);
    delay(AT_DELAY);
}


/**
 * @brief Sent AT command to HC-12 module.
 *
 * @param command Command
 */
void HC12::send_AT(String command)
{
    if (_SET_PIN == 0) return;
    digitalWrite(_SET_PIN, LOW);
    delay(AT_DELAY);
    // Send command
    _serial.print(command);
    delay(AT_DELAY);
    // Read response
    while(_serial.available() > 0) {
        char c = _serial.read();
    }
    digitalWrite(_SET_PIN, HIGH);
    delay(AT_DELAY);
}


/**
 * @brief Change serial port transparent transmission mode.
 *
 * @param mode HC12 mode.
 */
void HC12::set_mode(Mode mode)
{
    HC12::send_AT("AT+FU" + mode);
}


/**
 * @brief Set transmitting power of module.
 *
 * @param power Power value from 1 to 8.
 */
void HC12::set_power(short power)
{
    HC12::send_AT("AT+P" + String(power));
}


/**
 * @brief Set wireless communication channel.
 *
 * @param channel Channel number from 001 to 127.
 */
void HC12::set_channel(String channel)
{
    HC12::send_AT("AT+C" + channel);
}


/**
 * @brief Set serial port baud rate.
 *
 * @param baudrate Serial baudrate.
 * The baud rate can be set to be 1,200bps, 2,400bps, 4,800bps,
 * 9,600bps, 19,200bps, 38,400bps, 57,600bps, and 115,200bps.
 */
void HC12::set_baudrate(unsigned int baudrate)
{
    HC12::send_AT("AT+B" + String(baudrate));
}


/**
 * @brief Send message.
 *
 * @param message Message to be sent.
 */
void HC12::send(String message)
{
    _serial.print(message);
    // Wait for sending.
    unsigned long send_delay = message.length();
    switch (_MODE)
    {
        case FU1:  // Transmision data delay is 15-25 ms/byte.
        send_delay *= 25;
        break;

        case FU2:  // Transmision data delay is 500 ms/byte.
        send_delay *= 500;
        break;

        case FU3:  // Transmision data delay is 4-80 ms/byte.
        send_delay *= 80;
        break;
    }
    delay(send_delay);
}


/**
 * @brief Receive message.
 *
 * @param timeout Timeout. Min allowed value: 1000 ms.
 * @param end End line character.
 * @return Message.
 */
String HC12::receive(unsigned int timeout, char end)
{

    if (timeout < 1000) timeout = 1000;
    while(!_serial.available() && timeout > 0) {
        delay(50);
        timeout -= 50;
    }

    if (!timeout) {
        return "";
    }

    String msg;
    char byte;
    _serial.setTimeout(1000);
    while(_serial.available() && byte != end) {
        byte = char(_serial.read());
        msg += byte;
    }

    return msg;
}
