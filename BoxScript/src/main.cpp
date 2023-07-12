#include <Arduino.h>

#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <vector>
#include <led.h>
#include <drop.h>
#include <Servo.h>

#include <time_utils.h>
#include <parse_utils.h>
#include <display_utils.h>
#include <buzzer_utils.h>

#include <index.h>
#include <statistics.h>

// # # # define variables # # #

// setup
bool isAuthenticated = false;

int previousButtonState = LOW;

bool alertSent1 = true;
bool alertSent2 = true;
bool alertSent3 = true;
bool alertSent4 = true;

int page = 0;

std::vector<String> timerCol; //Vector array of set timers
std::vector<int> checkTimers; //Vector array of 0 or 1s to check if timer was used
std::vector<int> amountToDrop; //Vectory array storing the amount to drop

std::vector<String> timerColServer;
std::vector<int> checkTimersServer;
std::vector<int> amountToDropServer; //Vectory array storing the amount to drop

int totalPillCount = 0;
int totalPillCountPer = 0; // for percentage calculation
int totalPillCountServer = 0;
int totalPillCountServerPer = 0; // for percentage calculation

int pillsDropped = 0;
int pillsDroppedBox = 0;
int pillsDroppedServer = 0;
int threshold = 3;

Servo servo;
const int servoPin = D4;

// Pin definitions
const int redLED = D5;
const int yellowLED = D7;
const int whiteLED = D3;

const int buttonPin = D0;

const int buzzerPin = D6; 

// WiFi and server things
const char* ssid = ""; //Enter SSID
const char* password = ""; //Enter Password
const char* websockets_server_host = ""; //Enter server address
const char* toServer1 = "DropSinglePill";
const uint16_t websockets_server_port = 80; // Enter server port

ESP8266WebServer server(8080);

// # # # define functions # # #

void handleSetPillAmount();
void handleSetPillAmountServer();

void pillDropWrapper(int amount);       // is used for timer drops
void pillDropWrapperServer(int amount); // is used for timer drops

void handleSinglePillDrop();
void handleSinglePillDropServer();
void handleMultiplePillDropServer(int amount); // is used for timer drops

void handleSpecifiedPillDrop();
void handleSpecifiedPillDropServer();

void handleRootPage();

void handleSetTimerServer();
void handleSetTimer(); 

void handleResetAllTimer();
void handleResetAllTimerServer();

void handleDeleteAllTimer();
void handleDeleteAllTimerServer();

void handleLogin();
void handleLogout();

void handleStatisticsPage();

void pillWarning();
void changeDisplay(int page);

void checkConnection(int pin);

// time client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// websocket
using namespace websockets;

WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
        turnLEDOn(whiteLED);
        Serial.println("Connnection Opened");
    } else if (event == WebsocketsEvent::ConnectionClosed) {
        turnLEDOff(whiteLED);
        Serial.println("Connnection Closed");
    } else if (event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if (event == WebsocketsEvent::GotPong) {
        client.close();
    }
}

// # # # setup and loop # # #

void setup() {
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi ");

    // Wait some time to connect to wifi
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(200);
    }

    // Check if connected to wifi
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }

    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);

    Serial.println("Connected to Wifi, Connecting to server.");
    bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
    if (connected) {
        Serial.println("Connected!");
        client.send("First time connected to server");
        delay(1000);
        client.close();
    } else {
        Serial.println("Not Connected!");
    }

    server.on("/", HTTP_GET, []() {
        if (isAuthenticated) {
        handleRootPage();
            } else {
        server.send(200, "text/html", LOGIN_page);
        }
    });

    server.on("/login", HTTP_POST, handleLogin);

    server.on("/", HTTP_GET, []() {
    if (isAuthenticated) {
        handleRootPage();
    } else {
        server.send(200, "text/html", LOGIN_page);
    }
    });

    server.on("/login", handleLogout);

    server.on("/inputPillAmountBox", handleSetPillAmount);
    server.on("/inputPillAmountServer", handleSetPillAmountServer);

    server.on("/singelPillDrop", handleSinglePillDrop);
    server.on("/singelPillDropServer", handleSinglePillDropServer);

    server.on("/sendSpecifiedPillDrop", handleSpecifiedPillDrop);
    server.on("/sendSpecifiedPillDropServer", handleSpecifiedPillDropServer);

    server.on("/setTimer", handleSetTimer);
    server.on("/setServerTimer", handleSetTimerServer);

    server.on("/resetTimer", handleResetAllTimer);
    server.on("/resetTimerServer", handleResetAllTimerServer);

    server.on("/deleteTimer", handleDeleteAllTimer);
    server.on("/deleteTimerServer", handleDeleteAllTimerServer);

    server.on("/statistics", handleStatisticsPage);

    server.begin();
    Serial.print("Started Webserver! IP: ");
    Serial.println(WiFi.localIP());

    timeClient.begin();
    timeClient.setTimeOffset(7200);

    pinMode(redLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(whiteLED, OUTPUT);

    pinMode(buttonPin, INPUT_PULLUP);

    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(whiteLED, LOW);

    servo.attach(servoPin);
    servo.write(0);
    pinMode(buzzerPin, OUTPUT);

    displayStartingText();
    Serial.println("Setup finished correctly");
    displayBoxInformation(totalPillCount, totalPillCountPer, pillsDroppedBox, timerCol, checkTimers, timeClient.getFormattedTime());
}

void loop() {

  int buttonState = digitalRead(buttonPin);

    if (buttonState != previousButtonState) {

        if (buttonState == HIGH) {
            page++;
            Serial.println("Button is pressed");
            turnLEDOn(yellowLED);
            delay(200);
            turnLEDOff(yellowLED);
        } else {
            Serial.println("Button is not pressed");
        }
        previousButtonState = buttonState;
    }

    changeDisplay(page);

    timeClient.update();
    server.handleClient();

    if (isTimeEqual(timeClient.getFormattedTime(), "00:00:00")) {
        resetAllTimes(checkTimers, checkTimersServer);
    }

    int timeIndex = searchForTimeIndex(timeClient.getFormattedTime(), timerCol, checkTimers);
    int timeIndexServer = searchForTimeIndex(timeClient.getFormattedTime(), timerColServer, checkTimersServer);

    if (timeIndex != -1) {
        Serial.println("Pills to drop: " + (String)amountToDrop[timeIndex]);
        pillDropWrapper(amountToDrop[timeIndex]);
    }

    if (timeIndexServer != -1)
    {
        pillDropWrapperServer(amountToDropServer[timeIndexServer]);
        Serial.println("Pills to drop: " + (String)amountToDropServer[timeIndexServer]);
    }
    
    if (client.available()) {
        client.poll();
    }
    delay(200);
}

void handleSetPillAmount() {
    turnLEDOn(yellowLED);
    String input = server.arg("input");
    Serial.println("Input received!: " + input);

    if (!checkForDigits(input))
    {
        Serial.println("Parse error");
        server.send(200, "text/plain", "task failed");
        turnLEDOff(yellowLED);
        return;
    }
    
    totalPillCount = buildNumber(input);
    totalPillCountPer = buildNumber(input);

    alertSent1 = false;
    alertSent2 = false;

    Serial.println("New total pill count: " + input);
    server.send(200, "text/plain", "task done");
    delay(1000);
    turnLEDOff(yellowLED);
}

void handleSetPillAmountServer() {
    turnLEDOn(yellowLED);
    String inputServer = server.arg("input");
    Serial.println("Input received!: " + inputServer);

    if (!checkForDigits(inputServer))
    {
        Serial.println("Parse error");
        server.send(200, "text/plain", "task failed");
        turnLEDOff(yellowLED);
        return;
    }
    
    totalPillCountServer = buildNumber(inputServer);
    totalPillCountServerPer = buildNumber(inputServer);

    client.connect(websockets_server_host, websockets_server_port, "/");
    client.send("P" + inputServer);

    alertSent3 = false;
    alertSent4 = false;

    Serial.println("New total pill count on server: " + (String)totalPillCountServer);
    server.send(200, "text/plain", "task done");
    delay(1000);
    turnLEDOff(yellowLED);
}

void pillDropWrapper(int amount) {

    for (int i = 0; i < amount; i++)
    {
        handleSinglePillDrop();
    }
}

void pillDropWrapperServer(int amount) {
    handleMultiplePillDropServer(amount);
}

void handleSinglePillDrop() {
    Serial.println("Dropping single pill");

    displayProgressAnimation(20);
    delay(500);
    
    if (totalPillCount <= 0) {
        blinkLED(redLED, 3);
        Serial.println("Pills are empty, cannot drop.");
        turnLEDOn(redLED);
        server.send(200, "text/plain", "Pills are empty, cannot drop.");
        page = 2;
        displayProgressAnimation(100);
        buzzSimpleSignal(buzzerPin, 200, 700, 1000, 3);
        return;
    }

    displayProgressAnimation(40);
    
    turnLEDOff(redLED);
    moveServo(servo, servoPin);

    displayProgressAnimation(60);
    delay(500);

    totalPillCount--;
    pillsDropped++;
    pillsDroppedBox++;
    turnLEDOn(redLED);

    displayProgressAnimation(80);
    delay(500);
    
    server.send(200, "text/plain", "Pill dropped successfully.");

    displayProgressAnimation(100);
    Serial.println("Dropping single pill finished");
    pillWarning();

    if (totalPillCount <= 0)
    {
        buzzSimpleSignal(buzzerPin, 200, 700, 1000, 3);
        displayPillsEmptyWithAnim(totalPillCount, totalPillCountServer);
        page = 2;
        return;
    }
    buzzPillDropped(buzzerPin, 200, 700);
}


void handleSinglePillDropServer() {
    Serial.println("Dropping single pill server");
    client.connect(websockets_server_host, websockets_server_port, "/");

    displayProgressAnimation(20);

    if (totalPillCountServer <= 0)
    {   
        Serial.println("Tower pills are empty");
        server.send(200, "text/plain", "pills on tower are empty");
        client.send("BlinkRed");
        client.close();
        page = 2;
        displayProgressAnimation(100);
        buzzSimpleSignal(buzzerPin, 200, 700, 1000, 3);
        return;
    }

    turnLEDOn(yellowLED);
    client.send(toServer1);
    
    displayProgressAnimation(40);
    delay(2500);

    totalPillCountServer--;
    pillsDropped++;
    pillsDroppedServer++;

    displayProgressAnimation(60);
    delay(2500);

    delay(2500);
    turnLEDOff(yellowLED);

    displayProgressAnimation(80);
    delay(2500);

    displayProgressAnimation(100);
    server.send(200, "text/plain", "pill code executed!");
    pillWarning();

    if (totalPillCountServer <= 0)
    {   
        buzzSimpleSignal(buzzerPin, 200, 700, 1000, 3);
        displayPillsEmptyWithAnim(totalPillCount, totalPillCountServer);
        page = 2;
        return;
    }
}

void handleMultiplePillDropServer(int amount) {

    Serial.println("Dropping single pill server");
    client.connect(websockets_server_host, websockets_server_port, "/");

    displayProgressAnimation(20);

    if (totalPillCountServer <= 0)
    {   
        Serial.println("Tower pills are empty");
        server.send(200, "text/plain", "pills on tower are empty");
        client.send("BlinkRed");
        client.close();
        page = 2;
        displayProgressAnimation(100);
        buzzSimpleSignal(buzzerPin, 200, 700, 1000, 3);
        return;
    }

    turnLEDOn(yellowLED);
    client.send("D" + (String) amount);
    
    displayProgressAnimation(40);
    delay(2500);

    if (totalPillCountServer - amount <= 0){   
        int actualPillsDropped = totalPillCountServer;
        totalPillCountServer = 0;
        pillsDropped += actualPillsDropped;
        pillsDroppedServer += actualPillsDropped;
    } else {
        totalPillCountServer -= amount;
        pillsDropped += amount;
        pillsDroppedServer += amount;
    }

    displayProgressAnimation(60);
    delay(2500);

    delay(2500);
    turnLEDOff(yellowLED);

    displayProgressAnimation(80);
    delay(2500);

    displayProgressAnimation(100);
    server.send(200, "text/plain", "pill code executed!");
    pillWarning();

    if (totalPillCountServer <= 0)
    {   
        buzzSimpleSignal(buzzerPin, 200, 700, 1000, 3);
        displayPillsEmptyWithAnim(totalPillCount, totalPillCountServer);
        page = 2;
    } 
}

void handleSpecifiedPillDrop() {

    String amount = server.arg("specifiedAmount");
    pillDropWrapper(buildNumber(amount));
}

void handleSpecifiedPillDropServer() {

    String amount = server.arg("specifiedAmount");
    pillDropWrapperServer(buildNumber(amount));
}

void handleRootPage() {
    server.send(200, "text/html", MAIN_page);
}

void handleSetTimer() {
    turnLEDOn(yellowLED);

    String hours = server.arg("hours");
    String minutes = server.arg("minutes");
    String seconds = server.arg("seconds");
    String amountString = server.arg("boxAmount");

    int amount = buildNumber(amountString);

    String newTimer = createString(hours, minutes, seconds);

    String currentTime = timeClient.getFormattedTime();

    addNewTime(newTimer, timerCol, checkTimers, currentTime, amountToDrop, amount);

    Serial.println("New Timer: " + newTimer + " | Pills: " + amountString);
    server.send(200, "text/plain", "new timer was set!");

    delay(1000);
    turnLEDOff(yellowLED);
}

void handleSetTimerServer() {

    turnLEDOn(yellowLED);

    String hours = server.arg("hours");
    String minutes = server.arg("minutes");
    String seconds = server.arg("seconds");
    String amountString = server.arg("serverAmount");
    int amount = buildNumber(amountString);

    String newTimer = createString(hours, minutes, seconds);

    String currentTime = timeClient.getFormattedTime();

    addNewTime(newTimer, timerColServer, checkTimersServer, currentTime, amountToDropServer, amount);

    Serial.println("New Timer: " + newTimer + " | Pills: " + amountString);
    server.send(200, "text/plain", "new timer was set!");
    delay(1000);
    turnLEDOff(yellowLED);
}

void handleResetAllTimer() {
    resetAllTimesSpecific(checkTimers);
}

void handleResetAllTimerServer() {
    resetAllTimesSpecific(checkTimersServer);
}

void handleDeleteAllTimer() {
    deleteAllTimer(timerCol, checkTimers, amountToDrop);
}

void handleDeleteAllTimerServer() {
    deleteAllTimer(timerColServer, checkTimersServer, amountToDropServer);
}

void handleLogin() {
  if (server.hasArg("username") && server.hasArg("password")) {
    String username = server.arg("username");
    String password = server.arg("password");

    if (username == "admin" && password == "password") {
      isAuthenticated = true;
      server.sendHeader("Location", "/");
      server.send(302);
    } else {
      server.send(401, "text/html", "Authentication Failed");
    }
  } else {
    server.send(400, "text/html", "Bad Request");
  }
}

void handleLogout() {
    isAuthenticated = false;
    server.send(200, "text/html", LOGIN_page);
}

void handleStatisticsPage() {
    String page = getStatisticsPage(totalPillCount, totalPillCountPer, totalPillCountServer, totalPillCountServerPer, pillsDroppedBox, pillsDroppedServer, timerCol, checkTimers, amountToDrop, timerColServer, checkTimersServer, amountToDropServer, timeClient.getFormattedTime());
    server.send(200, "text/html", page);
}

void pillWarning() {
  float percentage = (float)totalPillCount / totalPillCountPer * 100;
  float percentage2 = (float)totalPillCountServer / totalPillCountServerPer  * 100;

  if (percentage <= 50 && percentage != 0 && !alertSent1) {
    alertSent1 = true;
    displayWarning();
    delay(1000);
    Serial.println("50% Alert was sent");
    return;
  }

  if (percentage <= 30 && percentage != 0 && !alertSent2) {
    alertSent2 = true;
    displayWarning();
    delay(1000);
    Serial.println("30% Alert was sent");
    return;
  }

  if (percentage2 <= 50 && percentage != 0 && !alertSent3) {
    alertSent3 = true;
    displayWarning();
    delay(1000);
    Serial.println("50% Alert was sent for server pill count");
    return;
  }

  if (percentage2 <= 30 && percentage2 != 0 &&!alertSent4) {
    alertSent4 = true;
    displayWarning();
    delay(1000);
    Serial.println("30% Alert was sent for server pill count");
    return;
  }
}

void changeDisplay(int page) {
  int endPage = page % 3;

  if (endPage == 0) {

    displayBoxInformation(totalPillCount, totalPillCountPer, pillsDroppedBox, timerCol, checkTimers, timeClient.getFormattedTime());
  } else if (endPage == 1) {

    displayServerInformation(totalPillCountServer, totalPillCountServerPer, pillsDroppedServer, timerColServer, checkTimersServer, timeClient.getFormattedTime());
  } else if (endPage == 2) {
    
    displayPillsEmpty(totalPillCount, totalPillCountServer);
  }
}
