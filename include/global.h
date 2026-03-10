#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

struct EnvironmentData {
    float temperature;
    float humidity;
};

extern QueueHandle_t QueueLCD;
extern QueueHandle_t QueueLED;
#endif // GLOBAL_H