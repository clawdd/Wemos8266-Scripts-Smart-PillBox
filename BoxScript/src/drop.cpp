#include <drop.h>
#include <Arduino.h>
#include <Servo.h>

/// @brief Moves the servo from the start to end postion to end postion again to drop a pill
///
/// @param servo The servo object
/// @param servoPin The servo pin
void moveServo(Servo servo, int servoPin) {

    for (int i = 0; i <= 180; i++)
    {
        servo.write(i);
        Serial.println("Servo position: " + String(i));
        delay(20);
    }

    Serial.println("Servo moved to end position");
    
    
    for (int i = 180; i >= 0; i--)
    {
        servo.write(i);
        Serial.println("Servo position: " + String(i));
        delay(20);
    }

    Serial.println("Servo moved to start position");
}