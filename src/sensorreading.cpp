#include "sensorreading.h"
#include "global.h"
#include "DHT20.h"

void readSensorData(void *pvParameters)
{
    DHT20 dht;
    dht.begin();

    EnvironmentData data;
    while(1){

    if(dht.read() == DHT20_OK)
    {
        data.temperature = dht.getTemperature();
        data.humidity = dht.getHumidity();

        xQueueOverwrite(QueueLCD, &data); 
        xQueueOverwrite(QueueLED, &data);
        xQueueOverwrite(QueueMQTT, &data);

        Serial.printf("[Sensor] Temp: %.1f°C | Hum: %.1f%%\n", data.temperature, data.humidity);
    } else {
        Serial.println("[Sensor] Failed to read data from DHT20");
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}
}
