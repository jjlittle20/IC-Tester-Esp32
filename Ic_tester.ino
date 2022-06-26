#include "ArduinoJson.h"

#include "FS.h"
#include "SD.h"
#include "SPI.h"

void readFile(fs::FS &fs, const char * path) {
  JsonObject root;
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  if (file) {
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, file);

    if (error) {
      Serial.println(F("Failed to read file, using default configuration"));
      Serial.println(error.c_str());
    };

    root = doc.as<JsonObject>();

    int pinCount = root["pinCount"];
    Serial.print("pinCount: ");
    Serial.println(pinCount);
  };


  file.close();
}

const int pin1 = 25 , pin2 = 26, pin4 = 27, pin5 = 14, pin6 = 34;


void setup() {
  Serial.begin(115200);
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);


  readFile(SD, "/config.txt");

  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));





  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, INPUT);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, HIGH);

  Serial.println(digitalRead(pin6));




}

void loop() {

}
