#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#include <display_utils.h>
#include <time_utils.h>
#include <bitmaps.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

/// @brief Displayes a give String aligned in the middle of the screen
///
/// @param text the desired text to be displayed
void displayNewText(String text) {
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    int textWidth = text.length() * 6 * 2;
    int x = (display.width() - textWidth) / 2;
    display.setCursor(x, 20);
    display.println(text);
    display.display();
}

/// @brief Plays the anim when the box is booting up using the bitmaps in the bitmaps.h file
///
void playBootingUpAnim() {
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    // Delay between frames in milliseconds
    const int frameDelay = 150;

    // Play animation forward
    for (int i = 0; i < epd_bitmap_allArray_LEN; i++) {
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_allArray[i], 128, 64, WHITE);
        display.display();
        delay(frameDelay);
    }

    display.clearDisplay();
    display.drawBitmap(0, 0, epd_bitmap_allArray[0], 128, 64, WHITE);
    delay(300);

    // Play animation in reverse
    for (int i = epd_bitmap_allArray_LEN - 2; i >= 0; i--) {
        display.clearDisplay();
        display.drawBitmap(0, 0, epd_bitmap_allArray[i], 128, 64, WHITE);
        display.display();
        delay(frameDelay);
    }

    // Draw frame 1 again at the end
    display.clearDisplay();
    display.drawBitmap(0, 0, epd_bitmap_allArray[0], 128, 64, WHITE);
    display.display();
}


/// @brief Calls all functions to display the text sequence + animation at the start
///
void displayStartingText() {
    displayNewText("Booting up");
    delay(1000);
    displayNewText("Your");
    delay(1000);
    displayNewText("Pill Box");
    delay(1000);
    playBootingUpAnim();
    displayNewText("Everything");
    delay(1000);
    displayNewText("Is");
    delay(1000);
    displayNewText("ready");
    delay(1000);
    displayNewText("to use!");
    delay(1000);
}

/// @brief Displays a progress bar to the desired progress point given to the function
///
/// @param progress The progress as int
void displayProgressAnimation(int progress) {
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  int progressBarWidth = SCREEN_WIDTH - 4;
  int progressBarHeight = 10;
  int progressBarX = 2;
  int progressBarY = (SCREEN_HEIGHT - progressBarHeight) / 2;

  int progressToShow = map(progress, 0, 100, 0, progressBarWidth);

  display.drawRect(progressBarX, progressBarY, progressBarWidth, progressBarHeight, SSD1306_WHITE);

  display.fillRect(progressBarX, progressBarY, progressToShow, progressBarHeight, SSD1306_WHITE);
  String labelText = "Pill Dropping";
  int textWidth = labelText.length() * 6;
  int textX = (SCREEN_WIDTH - textWidth) / 2;
  int textY = progressBarY - 10;
  display.setCursor(textX, textY);
  display.println(labelText);

  display.display();
}

/// @brief Displays the current box information for the user
///
/// @param pillCountBox The current pill count
/// @param pillCountPer The last set pill count
/// @param pillsDropped All pills dropped from the box since the last reset
/// @param timeVector A vector array containing all timers set
/// @param checkTimers A check vector for the timer
/// @param currentTime The current timer provided by the time client
void displayBoxInformation(int pillCountBox, int pillCountPer, int pillsDropped, const std::vector<String>& timeVector,
                           const std::vector<int>& checkTimers, String currentTime) {
  String pillCountString = String(pillCountBox);
  String pillCountPerString = String(pillCountPer);
  String pillsDroppedString = String(pillsDropped);
  String nextTimer = getSmallestNextTimer(timeVector, checkTimers, currentTime);

  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println("Box Information!");

  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

  display.println("");
  display.print("Pills: ");
  display.print(pillCountString);
  display.print("/");
  display.println(pillCountPerString);

  display.print("Dropped: ");
  display.println(pillsDroppedString);

  display.print("Next timer: ");
  display.setTextSize(2);

  int16_t x, y;
  uint16_t width, height;
  display.getTextBounds(nextTimer, 0, 0, &x, &y, &width, &height);

  int16_t textX = (SCREEN_WIDTH - width) / 2;
  int16_t textY = display.getCursorY() + height + 1; 

  int16_t bgWidth = width + 1;

  int16_t bgX = textX - 1;

  display.fillRect(bgX, textY - y, bgWidth, height, SSD1306_WHITE); 
  display.setCursor(textX, textY);
  display.setTextColor(SSD1306_BLACK);
  display.println(nextTimer);

  display.display();
}

/// @brief Displays the current tower information for the user
///
/// @param pillCountBox The current pill count
/// @param pillCountPer The last set pill count
/// @param pillsDropped All pills dropped from the tower since the last reset
/// @param timeVector A vector array containing all timers set
/// @param checkTimers A check vector for the timer
/// @param currentTime The current timer provided by the time client
void displayServerInformation(int pillCountBox, int pillCountPer, int pillsDropped, const std::vector<String>& timeVector,
                           const std::vector<int>& checkTimers, String currentTime) {
                            
  String pillCountString = String(pillCountBox);
  String pillCountPerString = String(pillCountPer);
  String pillsDroppedString = String(pillsDropped);
  String nextTimer = getSmallestNextTimer(timeVector, checkTimers, currentTime);

  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println("Tower Information!");

  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

  display.println("");
  display.print("Pills: ");
  display.print(pillCountString);
  display.print("/");
  display.println(pillCountPerString);

  display.print("Dropped: ");
  display.println(pillsDroppedString);

  display.print("Next timer: ");
  display.setTextSize(2);

  int16_t x, y;
  uint16_t width, height;
  display.getTextBounds(nextTimer, 0, 0, &x, &y, &width, &height);

  int16_t textX = (SCREEN_WIDTH - width) / 2;
  int16_t textY = display.getCursorY() + height + 1;

  int16_t bgWidth = width + 1;

  int16_t bgX = textX - 1;

  display.fillRect(bgX, textY - y, bgWidth, height, SSD1306_WHITE); 
  display.setCursor(textX, textY);
  display.setTextColor(SSD1306_BLACK);
  display.println(nextTimer);

  display.display();
}

/// @brief Displays the warning sequence when the pill count drops under the specified treshhold (30 and 50 percent)
///
void displayWarning () {

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    display.drawBitmap(0, 0, warning, 128, 64, WHITE);
    display.display();
    delay(1000);

    display.clearDisplay();
    displayNewText("Pills");
    delay(1000);
    displayNewText("are");
    delay(1000);
    displayNewText("low");
    delay(1000);

    display.drawBitmap(0, 0, warning, 128, 64, WHITE);
    delay(1000);

    display.display();
}

/// @brief Displays the pills status screen
///
/// @param totalPillCount the current pill count inside the box
/// @param totalPillCountServer the current pill count insied the tower
void displayPillsEmpty(int totalPillCount, int totalPillCountServer) {

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.println("Pill Status!");

    display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

    display.println("");
    display.print("Box: ");

    if (totalPillCount == 0){

        display.println("Empty");

    } else {
        String totalPillCountString = (String) totalPillCount;
        display.println(totalPillCountString);
    }

    display.setTextSize(1);
    display.print("Tower: ");

    if (totalPillCountServer == 0){

        display.println("Empty");

    } else {
        String totalPillCountServerString = (String) totalPillCountServer;
        display.println(totalPillCountServer);
    }

    if (totalPillCount <= 0 || totalPillCountServer <= 0) {
        display.setTextSize(2);
        int16_t x, y;
        uint16_t width, height;
        display.getTextBounds("REFILL", 0, 0, &x, &y, &width, &height);

        int16_t textX = (SCREEN_WIDTH - width) / 2;
        int16_t textY = display.getCursorY() + height + 1;

        int16_t bgWidth = width + 1;

        int16_t bgX = textX - 1;

        display.fillRect(bgX, textY - y, bgWidth, height, SSD1306_WHITE); 
        display.setCursor(textX, textY);
        display.setTextColor(SSD1306_BLACK);
        display.println("REFILL");
        display.display();
    }

    display.display();
}

/// @brief Gets called when the pills just got empty to play a small animation before showing the pills empty screen again
///
/// @param totalPillCount the current pill count inside the box
/// @param totalPillCountServer the current pill count inside the tower
void displayPillsEmptyWithAnim(int totalPillCount, int totalPillCountServer) {

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.println("Pill Status!");

    display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);

    display.println("");
    display.print("Box: ");

    if (totalPillCount == 0){

        display.println("Empty");

    } else {
        String totalPillCountString = (String) totalPillCount;
        display.println(totalPillCountString);
    }

    display.setTextSize(1);
    display.print("Tower: ");

    if (totalPillCountServer == 0){

        display.println("Empty");

    } else {
        String totalPillCountServerString = (String) totalPillCountServer;
        display.println(totalPillCountServer);
    }

    display.setTextSize(2);
    int16_t x, y;
    uint16_t width, height;
    display.getTextBounds("REFILL", 0, 0, &x, &y, &width, &height);

    int16_t textX = (SCREEN_WIDTH - width) / 2;
    int16_t textY = display.getCursorY() + height + 1;

    int16_t bgWidth = width + 1;

    int16_t bgX = textX - 1;

    display.fillRect(bgX, textY - y, bgWidth, height, SSD1306_WHITE); 
    display.setCursor(textX, textY);
    display.setTextColor(SSD1306_BLACK);
    display.println("REFILL");
    display.display();

    delay(500);

    display.fillRect(bgX, textY - y, bgWidth, height, SSD1306_BLACK); 
    display.setCursor(textX, textY);
    display.setTextColor(SSD1306_WHITE);
    display.println("REFILL");
    display.display();

    delay(500);

    display.fillRect(bgX, textY - y, bgWidth, height, SSD1306_WHITE); 
    display.setCursor(textX, textY);
    display.setTextColor(SSD1306_BLACK);
    display.println("REFILL");
    display.display();

    delay(500);

    display.fillRect(bgX, textY - y, bgWidth, height, SSD1306_BLACK); 
    display.setCursor(textX, textY);
    display.setTextColor(SSD1306_WHITE);
    display.println("REFILL");
    display.display();

    delay(500);

    display.display();
}