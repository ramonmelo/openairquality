#include "Arduino.h"

#include <SPI.h>
#include <SD.h>
#include "SensorTemp.cpp"


#define SD_CARD_PIN 15
#define SENSOR_PIN 5
#define RAIN_PIN 0


SensorTemp tempSensor(SENSOR_PIN, DHT22);

bool hasSD = false;

File logFile;

void setup()
{
    Serial.begin(9600); 
    while(!Serial) {}

    if (SD.begin(SD_CARD_PIN)) {
        hasSD = true;
    }

    logFile = SD.open("log.txt", FILE_WRITE);

    if (logFile) {
        logFile.println("testing 1 2 3");
        logFile.close();
    }
}

void loop()
{
    float temp;
    float humidity;
    tempSensor.info(temp, humidity);
    int rain = constrain(analogRead(RAIN_PIN), 0, 999);

    Serial.print(temp);
    Serial.print(humidity);
    Serial.println(rain);

    delay(500);
}
