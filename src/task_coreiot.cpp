#include "global.h"
#include "task_coreiot.h"
#include "WiFi.h"
#include <PubSubClient.h>

const char *coreIOT_server = "app.coreiot.io";
const char *coreIOT_token = "s1q8z3b1w3ipvmnizd3p";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void CoreIOT_Task(void *pvParameters)
{
    client.setServer(coreIOT_server, mqttPort);
    EnvironmentData data;

    while(1)
    {
    if (xSemaphoreTake(SemaphoreWifi, portMAX_DELAY) == pdTRUE)
    {
        xSemaphoreGive(SemaphoreWifi);

        if(!client.connected())
        {
         Serial.println("Connected to WiFi, starting CoreIOT task...");   
        client.connect("YoloUNO_Client", coreIOT_token, NULL);
        vTaskDelay(2000/portTICK_PERIOD_MS);
        continue;
        }
        client.loop();

        if(xQueueReceive(QueueMQTT, &data, 100 / portTICK_PERIOD_MS) == pdPASS)
        {
            String payload = String("{\"temperature\":") + String(data.temperature) + ",\"humidity\":" + String(data.humidity) + "}";
            client.publish("v1/devices/me/telemetry", payload.c_str());
            Serial.println("Published data to CoreIOT: " + payload);
        }
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);
}
}