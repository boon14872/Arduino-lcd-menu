#include <DHT.h>

class temp_service
{
    // use dht sensor to get temperature and humidity

private:
    int dht_pin;
    int dht_type;
    float temperature;
    float humidity;
    DHT dht;
    unsigned long lastReadTime;
    const unsigned long readInterval = 500; // Read temperature every 1 second

public:
    temp_service(int pin, int type) : dht(pin, type)
    {
        dht_pin = pin;
        dht_type = type;
        dht.begin();
        lastReadTime = 0;
    }

    void readTemp()
    {
        unsigned long currentTime = millis();
        if (currentTime - lastReadTime >= readInterval)
        {
            temperature = dht.readTemperature();
            humidity = dht.readHumidity();
            lastReadTime = currentTime;
        }
    }

    float getTemp()
    {
        return temperature;
    }

    float getHumidity()
    {
        return humidity;
    }
};
