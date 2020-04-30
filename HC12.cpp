#include "HC12.hpp"

/**
 * @brief Construct a new HC12 object.
 *
 * @param RX_Pin RXD pin on HC12 module.
 * @param TX_Pin TXD pin on HC12 module.
 */
HC12::HC12(uint8_t RX_Pin, uint8_t TX_Pin): _serial(SoftwareSerial(RX_Pin, TX_Pin)), _SET_PIN(0) {}


/**
 * @brief Construct a new HC12 object.
 *
 * @param RX_Pin RXD pin on HC12 module.
 * @param TX_Pin TXD pin on HC12 module.
 * @param SET_Pin SET pin on HC12 module.
 */
HC12::HC12(uint8_t RX_Pin, uint8_t TX_Pin, uint8_t SET_Pin): _serial(SoftwareSerial(RX_Pin, TX_Pin)), _SET_PIN(SET_Pin) {}


/**
 * @brief Initialize the communication with the HC12 module.
 */
void HC12::begin(void)
{
    _serial.begin(9600);
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
void HC12::sleep(void) {
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
void HC12::wakeup(void) {
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
 * @brief Change serial port transparent transmission mode.
 *
 * @param mode HC12 mode.
 */
void HC12::setup_mode(Mode mode) {
    digitalWrite(_SET_PIN, LOW);
    delay(AT_DELAY);
    // Send command
    _serial.print("AT+FU" + mode);
    delay(AT_DELAY);
    // Read response
    while(_serial.available() > 0) {
        char c = _serial.read();
    }
    digitalWrite(_SET_PIN, HIGH);
    delay(AT_DELAY);
}


/**
 * @brief Set transmitting power of module.
 *
 * @param power Power value from 1 to 8.
 */
void HC12::setup_power(short power) {
    digitalWrite(_SET_PIN, LOW);
    delay(AT_DELAY);
    // Send command
    _serial.print("AT+P" + String(power));
    delay(AT_DELAY);
    // Read response
    while(_serial.available() > 0) {
        char c = _serial.read();
    }
    digitalWrite(_SET_PIN, HIGH);
    delay(AT_DELAY);
}
