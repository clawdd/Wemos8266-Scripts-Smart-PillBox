#include <Arduino.h>
#include <parse_utils.h>

int parseStringToInt(String str) {

    int totalNumber = 0;

    for (char c : str)
    {
        if (isdigit(c))
        {
            int digit = ((int)c) - 48;
            totalNumber = (10 * totalNumber + digit);
        }
    }
    return totalNumber;
}