#include <Arduino.h>

    String getStatisticsPage(int pillCount, int pillCountServer, int pillsDropped, const std::vector<String>& timeVector,
                             std::vector<int>& pillsToDrop, const std::vector<String>& timeVectorServer, 
                             std::vector<int>& pillsToDropServer);