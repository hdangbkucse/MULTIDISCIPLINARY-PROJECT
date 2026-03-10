#include "global.h"
#include "led.h"
#include <Adafruit_NeoPixel.h>

void LED_Control(void *pvParameters)
{
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.clear();
    strip.show();

    EnvironmentData data_receive;

    while (1)
    {
        if (xQueueReceive(QueueLED, &data_receive, portMAX_DELAY) == pdPASS)
        {
            float humidity = data_receive.humidity;

            uint32_t color;
            String status;
            String colorName;

            if (humidity < 0 || isnan(humidity))
            {
                color = strip.Color(255, 255, 255); // Trắng
                status = "ERROR";
                colorName = "White";
            }
            else if (humidity >= 0 && humidity < 60)
            {
                color = strip.Color(255, 0, 0); // Đỏ
                status = "LOW";
                colorName = "Red";
            }
            else if (humidity >= 60 && humidity < 80)
            {
                color = strip.Color(0, 255, 0); // Xanh lá
                status = "NORMAL";
                colorName = "Green";
            }
            else
            {
                color = strip.Color(0, 0, 255); // Xanh dương
                status = "WET";
                colorName = "Blue";
            }

            strip.setPixelColor(0, color);
            strip.show();
        }
    }
}