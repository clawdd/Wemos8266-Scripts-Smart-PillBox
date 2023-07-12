#include <Arduino.h>
#include <Servo.h>

#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

#include <led.h>
#include <drop.h>
#include <parse_utils.h>

// # # # define variables # # # 

int totalPillCount = 0;

Servo servo;
const int servoPin = D4;

//Pin definitions

const int redLED = D5;

// Wifi and server things
const char* ssid = ""; // SSID
const char* password = ""; // Password

// # # # define functions # # #

void handleSetPillCount(String msg);
void parseMessage(String msg);
void handleSinglePillDrop();
void handleMultiplePillDrop(int amount);
void sendToClient(String msg);

using namespace websockets;

WebsocketsServer server;
WebsocketsClient client;

// # # # setup and loop # # #

void setup() {

  Serial.begin(115200);
  // Connect to wifi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi ");

  // Wait some time to connect to wifi
  while(WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(200);
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.listen(80);
  Serial.print("Is server live? ");
  Serial.println(server.available());

  servo.attach(servoPin);
  servo.write(0);

  pinMode(redLED, OUTPUT);
  digitalWrite(redLED, HIGH);
}

void loop() {
  if(!client.available()) {
    client = server.accept();
  }

  if(client.available()) {
    WebsocketsMessage msg = client.readBlocking();

    // log
    Serial.print("Got Message: ");
    Serial.println(msg.data());

    parseMessage(msg.data());
  }

  delay(1000);
}

//# # # function declarations # # #

void handleSetPillCount(String msg) {

  sendToClient("TaskRunning");
  totalPillCount = parseStringToInt(msg);
  Serial.println("New total pill count: " + (String)totalPillCount);
  delay(1000);
  sendToClient("TaskFinished");
}

void parseMessage(String msg) {

  if(msg == "DropSinglePill") {

    handleSinglePillDrop();
    return;
  }

  if (msg == "BlinkRed") {
    blinkLED(redLED, 3);
    return;
  }

  for (char c : msg)
  {
    if (c == 'P') 
    {
      handleSetPillCount(msg);
      return;
    }
  }

  for (char c : msg)
  {
    if (c == 'D') 
    {
      handleMultiplePillDrop(parseStringToInt(msg));
      return;
    }
  }
  
  client.send("Echo: " + msg);
}

void handleSinglePillDrop() {

  if (totalPillCount <= 0){
    blinkLED(redLED, 3);
    Serial.println("Pills are empty cannot drop.");
    sendToClient("TaskFailed");
    return;
  }

  turnLedOff(redLED);

  sendToClient("TaskRunning");

  moveServo(servo, servoPin);
  totalPillCount--;

  turnLEDon(redLED);
  sendToClient("TaskFinished");
}

void handleMultiplePillDrop(int amount) {

  for (int i = 0; i < amount; i++)
  {
    Serial.println("Dropping pill num: " + ((String) i + 1));
    handleSinglePillDrop();
    delay(1000);
  }
}

void sendToClient(String msg) {
  
  if (msg == "TaskRunning") {
    client.ping();
  }
  if (msg == "TaskFinished") {
    client.pong();
  }
  if (msg == "TaskFailed")
  {
    client.pong();
  }
}