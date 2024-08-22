#include "MenuService.h"
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define JOY_X_PIN A0
#define JOY_Y_PIN A1
#define JOY_BUTTON_PIN 3

#define RELAY_PIN 7

MenuService menuService(LCD_ADDR, LCD_COLS, LCD_ROWS, JOY_X_PIN, JOY_Y_PIN, JOY_BUTTON_PIN, RELAY_PIN);

void setup()
{
    Serial.begin(115200);
    menuService.init();
}

void loop()
{
    menuService.update();
}
