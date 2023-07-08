#include <vector>
#include <Arduino.h>

void addNewTime(String newTime, std::vector<String>& timeVector, std::vector<int>& checkTimers,
                String currentTime, std::vector<int>& amountToDrop, int amount);


//!!!This version is for the daily 00:00:00 reset!!!
void resetAllTimes(std::vector<int>& checkTimers1, std::vector<int>& checkTimers2);

void resetAllTimesSpecific(std::vector<int>& checkTimers);

void deleteAllTimer(std::vector<String>& timerCol, std::vector<int>& checkTimers, std::vector<int>& amountToDrop);

bool searchForTime(String actualTime, const std::vector<String>& timeVector, std::vector<int>& checkTimers);

int searchForTimeIndex(String actualTime, const std::vector<String>& timeVector, std::vector<int>& checkTimers);

String createString(String one, String two, String three);

bool isTimeSmaller(const String& time1, const String& time2);

bool isTimeEqual(const String& time1, const String& time2);

String getSmallestNextTimer(const std::vector<String>& timeVector, const std::vector<int>& checkTimers, String currentTimer);