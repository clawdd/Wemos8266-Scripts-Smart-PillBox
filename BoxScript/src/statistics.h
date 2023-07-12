#include <Arduino.h>
#include <vector>

String getStatisticsPage(int currentPills, int pillPer, int currentPillsTower, int pillPerTower, int totalDropped, int totalDroppedTower,
                         std::vector<String>& timeVector, std::vector<int>& checkTimers, std::vector<int>& amountToDrop,
                         std::vector<String>& timeVectorTower, std::vector<int>& checkTimersTower, std::vector<int>& amountToDropTower, String currentTimer);