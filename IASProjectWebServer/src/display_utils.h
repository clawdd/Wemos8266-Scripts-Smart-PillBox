#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

void displayNewText(String text);

void clearDisplay();

void displayStartingText();

void displayTestText(); //For debugging

void displayCurrentPillCount(int pillCountBox, int pillCountServer);

void displayProgressAnimation (int progress);

void displayBoxInformation (int pillCountBox, int pillCountBoxPer, int pillsDropped, const std::vector<String>& timeVector, 
                            const std::vector<int>& checkTimers, String currentTime);

void displayServerInformation(int pillCountBox, int pillCountPer, int pillsDropped, const std::vector<String>& timeVector,
                           const std::vector<int>& checkTimers, String currentTime);

void displayWarning ();

void displayPillsEmpty(int totalPillCount, int totalPillCountServer);

void displayPillsEmptyWithAnim(int totalPillCount, int totalPillCountServer);