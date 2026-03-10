#include "global.h"
#include "lcd.h"
#include "LiquidCrystal_I2C.h"

void LCD_Display(void *pvParameters)
{
    LiquidCrystal_I2C lcd(33, 16, 2);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Display Data");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    EnvironmentData data;
    while (1)
    {
        if (xQueueReceive(QueueLCD, &data, portMAX_DELAY) == pdPASS)
        {
            lcd.setCursor(0, 0);
            lcd.printf("Temp: %.1f C  ", data.temperature);
            lcd.setCursor(0, 1);
            lcd.printf("Humi: %.1f %% ", data.humidity);
        }
    }
}