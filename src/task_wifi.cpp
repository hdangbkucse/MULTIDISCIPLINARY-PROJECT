#include "global.h"
#include "task_wifi.h"
#include <WiFi.h>

const char *wifi_ssid = "hdang";
const char *wifi_password = "hdangbachkhoa";
void taskWifi(void *pvParameters)
{
    WiFi.mode(WIFI_STA);
    while(1)
    {
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("Connecting to Wifi...");
        WiFi.disconnect();
        WiFi.begin(wifi_ssid, wifi_password);

        while (WiFi.status() != WL_CONNECTED)
        {
            vTaskDelay(500 / portTICK_PERIOD_MS);
            Serial.print(".");
        }
        Serial.println(" Connected!");
        Serial.print("[WiFi Task] IP Address: ");
        Serial.println(WiFi.localIP());
        if (SemaphoreWifi!= NULL)
        {
            xSemaphoreGive(SemaphoreWifi);
        }
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);
}
}