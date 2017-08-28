#include "Arduino.h"

#include <SPI.h>
#include <SD.h>
#include "SensorTemp.cpp"

#include "Wire.h"
#include "RTClib.h"

#define SD_CARD_PIN 15
#define SENSOR_PIN 5
#define RAIN_PIN 0

#define SDA_PIN 0
#define SCL_PIN 2

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
RTC_DS1307 rtc;

SensorTemp tempSensor(SENSOR_PIN, DHT22);

bool hasSD = false;

File logFile;

void setup()
{
    Serial.begin(9600); 
    while(!Serial) {}

    Wire.begin(SDA_PIN, SCL_PIN);

    if (!rtc.isrunning()) {
        Serial.println("RTC is NOT running!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

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
    int temp;
    int humidity;
    tempSensor.info(temp, humidity);
    int rain = constrain(analogRead(RAIN_PIN), 0, 999);

    Serial.println(temp);
    Serial.println(humidity);
    Serial.println(rain);

    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.println("-------------------------------");

    delay(500);
}
