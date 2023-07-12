#include <Arduino.h>
#include <buzzer_utils.h>

/// @brief Buzzer one time when a pill is dropped succesfully
///
/// @param pin The Buzzer pin
/// @param frequency The desired frequency
/// @param duaration  The duaration of the buzz
void buzzPillDropped(int pin, double frequency, int duaration) {
    Serial.println("Buzzer buzzing");
    tone(pin, frequency, duaration);
}

/// @brief Does buzz a simple signal given the wished parameters in a periodic way
/// 
/// @param pin The Buzzer pin
/// @param frequency The desired frequency
/// @param duaration  The duaration of the buzz
/// @param delayA The delay between each sound
/// @param count How often the sound should be played
void buzzSimpleSignal(int pin, double frequency, int duaration, int delayA, int count) {

    for (int i = 0; i < count; i++)
    {
        tone(pin, frequency, duaration);
        delay(delayA);
    }
}