
#include "Arduino.h"

#define LED 13

void setup() 
{
    pinMode(LED, OUTPUT);
    Serial.begin(9600);

}

void loop()
{
    digitalWrite(LED, HIGH);
    delay(500);

    Serial.write("teste");

    digitalWrite(LED, LOW);
    delay(500);
}