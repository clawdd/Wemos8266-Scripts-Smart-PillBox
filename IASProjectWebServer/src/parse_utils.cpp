#include <Arduino.h>
#include <parse_utils.h>

bool checkForDigits(String str) {

    for (char c : str) {
        if (!isdigit(c))    
        {
            return false;
        }
    }
    return true;
}

int buildNumber (String str) {

    int totalNumber = 0;

    for (char c : str) {

        int digit = ((int)c) - 48;
        totalNumber = (10 * totalNumber + digit);
    }
    return totalNumber;
}