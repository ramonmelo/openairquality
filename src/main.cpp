#include "Arduino.h"

#include "SensorTemp.cpp"

SensorTemp tempSensor(5, DHT22);

void setup()
{
    Serial.begin(9600); 
}

void loop()
{
    float temp;
    float humidity;

    tempSensor.info(temp, humidity);

    Serial.print(temp); Serial.println("*C\n");
    Serial.print(humidity); Serial.println("%\n");
    Serial.println("-----------------\n");

    delay(500);
}
