#include <Arduino.h>
#include <led.h>

/// @brief Turns a led off
///
/// @param led the led pin
void turnLEDOff(int led) {

    digitalWrite(led, LOW);
    Serial.println("LED Off");
}

/// @brief Turns a led on
///
/// @param led the led pin
void turnLEDOn(int led) {
    digitalWrite(led, HIGH);
    Serial.println("LED On");
}

/// @brief Blinks a led for the given count
///
/// @param led the led pin
/// @param count the amount of blinks
void blinkLED(int led, int count) {
    
    for (int i = 0; i <= count; i++)
    {
        
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
    }
    digitalWrite(led, LOW);
    Serial.println("LED blinked");
}