#include <vector>
#include <string>
#include <algorithm>
#include <Arduino.h>
#include <time_utils.h>

/// @brief Adds a new time to the given vector arrays
///
/// @param newTime the new time 
/// @param timeVector the vector array containing the time
/// @param checkTimers a check vector array deciding if the timer already was used or not
/// @param currentTime the current time
/// @param amountToDrop a vector array containing the amount to be dropped
/// @param amount the amount to be dropped
void addNewTime(String newTime, std::vector<String>& timeVector, std::vector<int>& checkTimers,
                String currentTime, std::vector<int>& amountToDrop, int amount) {

    timeVector.push_back(newTime);
    
    if(isTimeSmaller(currentTime, newTime)) {
        checkTimers.push_back(0);
        amountToDrop.push_back(amount);
        return;
    }
    checkTimers.push_back(1);
    amountToDrop.push_back(amount);
}


/// @brief resets all timer to be unused
///
/// @param checkTimers1 the vector array containing the box / tower timer
/// @param checkTimers2 the vector array containing the box / tower timer
void resetAllTimes(std::vector<int>& checkTimers1, std::vector<int>& checkTimers2) {

    for (size_t i = 0; i < checkTimers1.size(); i++)
    {
        checkTimers1[i] = 0;
    }
    
    for (size_t i = 0; i < checkTimers2.size(); i++)
    {
        checkTimers1[i] = 0;
    }
}

/// @brief resets all timer of the box or the tower
///
/// @param checkTimers the vector array thats has been chosen to be reseted
void resetAllTimesSpecific(std::vector<int>& checkTimers) {

    for (size_t i = 0; i < checkTimers.size(); i++)
    {
        checkTimers[i] = 0;
    }
}

void deleteAllTimer(std::vector<String>& timerCol, std::vector<int>& checkTimers, std::vector<int>& amountToDrop) {

    timerCol.clear();
    checkTimers.clear();
    amountToDrop.clear();

}

// We search for a timer which is smaller or equals the current time and check if it has been used

bool searchForTime(String actualTime, const std::vector<String>& timeVector, std::vector<int>& checkTimers) {
    int i = 0; // position in array

    for (const String& time : timeVector) {
        if (isTimeSmaller(time, actualTime) && checkTimers[i] == 0) {
            checkTimers[i] = 1;
            return true;
        }
        i++;
    }
    return false;
}

// We search for a timer which is smaller or equals the current time and check if it has been used but return the index

int searchForTimeIndex(String actualTime, const std::vector<String>& timeVector, std::vector<int>& checkTimers) {
    int i = 0; // position in array

    for (const String& time : timeVector) {
        if (isTimeSmaller(time, actualTime) && checkTimers[i] == 0) {
            checkTimers[i] = 1;
            return i;
        }
        i++;
    }
    return -1;
}

String createString(String one, String two, String three) {
    String created = one + ":" + two + ":" + three;
    return created;
}

bool isTimeSmaller(const String& time1, const String& time2) {
    String timeCopy1 = time1;
    String timeCopy2 = time2;

    timeCopy1.replace(":", "");
    timeCopy2.replace(":", "");

    int timeValue1 = timeCopy1.toInt();
    int timeValue2 = timeCopy2.toInt();

    return timeValue1 <= timeValue2;
}

bool isTimeEqual(const String& time1, const String& time2) {
        String timeCopy1 = time1;
    String timeCopy2 = time2;

    timeCopy1.replace(":", "");
    timeCopy2.replace(":", "");

    int timeValue1 = timeCopy1.toInt();
    int timeValue2 = timeCopy2.toInt();

    // Compare the time values
    return timeValue1 == timeValue2;
}

String getSmallestNextTimer(const std::vector<String>& timeVector, const std::vector<int>& checkTimers, String currentTimer) {
    if (timeVector.empty()) {
        return "No Timer";
    }

    String compareTime = "9999:59:59";  // Set an initial maximum value

    for (size_t i = 0; i < timeVector.size(); i++) {
        if (isTimeSmaller(timeVector[i], compareTime) && isTimeSmaller(currentTimer, timeVector[i]) && checkTimers[i] == 0) {
            compareTime = timeVector[i];
        }
    }

    if (compareTime == "9999:59:59") {
        return "No Timer";
    }

    return compareTime;
}

