#include <Arduino.h>
#include <buzzer_utils.h>

void buzzPillDropped(int pin, double frequency, int duaration) {
    Serial.println("Buzzer buzzing");
    tone(pin, frequency, duaration);
}

void buzzSimpleSignal(int pin, double frequency, int duaration, int delayA, int count) {

    for (int i = 0; i < count; i++)
    {
        tone(pin, frequency, duaration);
        delay(delayA);
    }
}