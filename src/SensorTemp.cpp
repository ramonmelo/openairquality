#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class SensorTemp
{
    private:
        DHT_Unified sensor;
        long lastTime;

        int lastTemp;
        int lastHumidity;

    public: 
        SensorTemp(uint8_t pin, uint8_t type) : sensor(pin, type) {
            sensor.begin();
        }

        void info(float &temperature, float &humidity) {
            if ((millis() - lastTime) > 1000) {
                sensors_event_t event;
    
                // Read temperature
                sensor.temperature().getEvent(&event);
                lastTemp = isnan(event.temperature) ? -1 : int(event.temperature * 100);
                
                // Read relative humidity
                sensor.humidity().getEvent(&event);
                lastHumidity = isnan(event.relative_humidity) ? -1 : int(event.relative_humidity * 100);

                lastTime = millis();
            }

            temperature = lastTemp;
            humidity = lastHumidity;
        }
};