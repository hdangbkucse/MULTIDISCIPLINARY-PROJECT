#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/semphr.h>

struct EnvironmentData {
    float temperature;
    float humidity;
};

extern QueueHandle_t QueueLCD;
extern QueueHandle_t QueueLED;
extern QueueHandle_t QueueMQTT;
extern SemaphoreHandle_t SemaphoreWifi;
#endif // GLOBAL_H