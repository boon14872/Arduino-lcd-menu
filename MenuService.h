#ifndef MENU_SERVICE_H
#define MENU_SERVICE_H

#define DEBOUNCE_DELAY 200

// green tea: 80°C, 3 minutes
// black tea: 100°C, 5 minutes

#define GREEN_TEA_TEMP 80
#define GREEN_TEA_TIME 1

#define BLACK_TEA_TEMP 100
#define BLACK_TEA_TIME 1

#include <LiquidCrystal_I2C.h>
#include "JoyService.h"

enum MenuOption
{
    MENU_GREEN_TEA,
    MENU_BLACK_TEA,
    MENU_CUSTOM,
    MENU_START,
    MENU_BACK,
    MENU_STOP,
    MENU_SET_TIME
};

enum MenuState
{
    STATE_MAIN_MENU,
    STATE_GREEN_TEA,
    STATE_BLACK_TEA,
    STATE_CUSTOM,
    STATE_RUNNING,
    STATE_SET_TIME
};

class MenuService
{
public:
    MenuService(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows, uint8_t joyXPin, uint8_t joyYPin, uint8_t joyButtonPin, uint8_t relayPin);

    void init();
    void update();

private:
    LiquidCrystal_I2C lcd;
    JoyService joy;
    uint8_t relayPin;

    MenuState currentState;
    MenuOption currentOption;

    int customTemperature;
    int customTime;

    unsigned long startTime;
    unsigned long brewDuration;
    unsigned long debounceDelay;
    unsigned long lastInputTime;

    void displayMainMenu();
    void displaySubMenu();
    void displayProgress();
    void displaySetTime();
    void handleInput();
    void startBrew(int timeInMinutes);
    void stopBrew();
};

#endif // MENU_SERVICE_H
