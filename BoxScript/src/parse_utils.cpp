#include <Arduino.h>
#include <parse_utils.h>

/// @brief checks if a string contains only digits
///
/// @param str the string to be checkd
/// @return true or false
bool checkForDigits(String str) {

    for (char c : str) {
        if (!isdigit(c))    
        {
            return false;
        }
    }
    return true;
}

/// @brief Builds the number from a String
///
/// @param str the given String
/// @return the number as int
int buildNumber (String str) {

    int totalNumber = 0;

    for (char c : str) {

        int digit = ((int)c) - 48;
        totalNumber = (10 * totalNumber + digit);
    }
    return totalNumber;
}