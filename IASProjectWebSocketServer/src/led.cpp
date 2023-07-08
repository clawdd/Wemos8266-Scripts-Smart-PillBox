#include <Arduino.h>
#include <led.h>

void turnLedOff (int led) {
    digitalWrite(led, LOW);
    Serial.println("LED Off");
}

void turnLEDon (int led) {
    digitalWrite(led, HIGH);
    Serial.println("LED On");
}

void blinkLED (int led, int count) {

    for (int i = 0; i <= count; i++)
    {
        
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
    }
    digitalWrite(led, HIGH);
    Serial.println("LED blinked");
}