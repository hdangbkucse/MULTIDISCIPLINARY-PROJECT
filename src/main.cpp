#include <Arduino.h>
#include <Wire.h>
#include "global.h"
#include "sensorreading.h"
#include "lcd.h"
#include "led.h"
#include "task_wifi.h"
#include "task_coreiot.h"

#define SDA_PIN 11
#define SCL_PIN 12

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  QueueLCD = xQueueCreate(1, sizeof(EnvironmentData));
  QueueLED = xQueueCreate(1, sizeof(EnvironmentData));
  QueueMQTT = xQueueCreate(1, sizeof(EnvironmentData));
  SemaphoreWifi = xSemaphoreCreateBinary();

  if (QueueLCD != NULL && QueueLED != NULL && SemaphoreWifi != NULL && QueueMQTT != NULL)
  {
    xTaskCreate(readSensorData, "sensorData", 4096, NULL, 2, NULL);
    xTaskCreate(LCD_Display, "lcdDisplay", 4096, NULL, 2, NULL);
    xTaskCreate(LED_Control, "ledControl", 4096, NULL, 2, NULL);
    xTaskCreate(taskWifi, "wifiTask", 4096, NULL, 2, NULL);
    xTaskCreate(CoreIOT_Task, "coreIOTTask", 4096, NULL, 2, NULL);
  }
  else
  {
    Serial.println("Failed to create queues");
  }
}

void loop()
{
  // Serial.println("Hello Custom Board");
  // delay(1000);
}