#include "joy_service.h"
#include <LiquidCrystal_I2C.h>

enum MenuOption
{
    MENU_GREEN_TEA,
    MENU_BLACK_TEA,
    MENU_CUSTOM,
    MENU_START,
    MENU_BACK,
    MENU_STOP,
    MENU_NONE
};

enum MenuState
{
    STATE_MAIN_MENU,
    STATE_GREEN_TEA,
    STATE_BLACK_TEA,
    STATE_CUSTOM,
    STATE_RUNNING
};

class MenuService
{
private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
    JoyService joy = JoyService(A0, A1, 3);
    const int relayPin = 7; // Pin connected to the relay

    MenuState currentState = STATE_MAIN_MENU;
    MenuOption currentOption = MENU_GREEN_TEA;

    int customTemperature = 75;  // Default custom temperature
    int customTime = 3;          // Default custom time (minutes)

    unsigned long startTime = 0;       // Time when the brewing process starts
    unsigned long brewDuration = 0;    // Duration of the brewing process in milliseconds
    unsigned long debounceDelay = 1000; // Debounce delay in milliseconds
    unsigned long lastInputTime = 0;   // Time of the last input

    void displayMainMenu();
    void displaySubMenu();
    void displayProgress();
    void handleInput();
    void startBrew(int timeInMinutes);
    void stopBrew();

public:
    void init();
    void update();

    void setup() { init(); }
    void loop() { update(); }
};

void MenuService::init()
{
    lcd.init();
    lcd.backlight();
    joy.init();
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW); // Ensure relay is off at the start

    displayMainMenu();
}

void MenuService::update()
{
    handleInput();

    if (currentState == STATE_RUNNING)
    {
        // Calculate remaining time
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - startTime;

        if (elapsedTime >= brewDuration)
        {
            stopBrew();
        }
        else
        {
            displayProgress();
        }
    }
}

void MenuService::displayMainMenu()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Select Tea:");
    lcd.setCursor(0, 1);
    switch (currentOption)
    {
    case MENU_GREEN_TEA:
        lcd.print("> Green Tea");
        break;
    case MENU_BLACK_TEA:
        lcd.print("> Black Tea");
        break;
    case MENU_CUSTOM:
        lcd.print("> Custom");
        break;
    default:
        break;
    }
}

void MenuService::displaySubMenu()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    switch (currentState)
    {
    case STATE_GREEN_TEA:
        lcd.print("Green Tea");
        break;
    case STATE_BLACK_TEA:
        lcd.print("Black Tea");
        break;
    case STATE_CUSTOM:
        lcd.print("Custom");
        break;
    default:
        break;
    }

    lcd.setCursor(0, 1);
    if (currentOption == MENU_START)
    {
        lcd.print("> Start");
    }
    else if (currentOption == MENU_BACK)
    {
        lcd.print("> Back");
    }
    else if (currentOption == MENU_STOP)
    {
        lcd.print("> Stop");
    }
}
void MenuService::displayProgress()
{
    static unsigned long lastDisplayTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastDisplayTime < 300)
    {
        return;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Brewing...");

    unsigned long remainingTime = (brewDuration - (currentTime - startTime)) / 1000;
    lcd.setCursor(0, 1);
    lcd.print("Time left: ");
    lcd.print(remainingTime / 60);
    lcd.print(":");
    lcd.print(remainingTime % 60);

    lastDisplayTime = currentTime;
}

void MenuService::handleInput()
{
    unsigned long currentTime = millis();

    if (currentTime - lastInputTime < debounceDelay)
    {
        return;
    }

    JoyDirection dir = joy.read();

    if (currentState == STATE_MAIN_MENU)
    {
        if (dir == JOY_UP)
        {
            if (currentOption == MENU_GREEN_TEA)
                currentOption = MENU_CUSTOM;
            else
                currentOption = static_cast<MenuOption>(currentOption - 1);
            displayMainMenu();
            lastInputTime = currentTime;
        }
        else if (dir == JOY_DOWN)
        {
            if (currentOption == MENU_CUSTOM)
                currentOption = MENU_GREEN_TEA;
            else
                currentOption = static_cast<MenuOption>(currentOption + 1);
            displayMainMenu();
            lastInputTime = currentTime;
        }
        else if (dir == JOY_PRESS)
        {
            switch (currentOption)
            {
            case MENU_GREEN_TEA:
                currentState = STATE_GREEN_TEA;
                currentOption = MENU_START;
                displaySubMenu();
                break;
            case MENU_BLACK_TEA:
                currentState = STATE_BLACK_TEA;
                currentOption = MENU_START;
                displaySubMenu();
                break;
            case MENU_CUSTOM:
                currentState = STATE_CUSTOM;
                currentOption = MENU_START;
                displaySubMenu();
                break;
            default:
                break;
            }
            lastInputTime = currentTime;
        }
    }
    else if (currentState == STATE_GREEN_TEA || currentState == STATE_BLACK_TEA || currentState == STATE_CUSTOM)
    {
        if (dir == JOY_UP || dir == JOY_DOWN)
        {
            currentOption = (currentOption == MENU_START) ? MENU_BACK : MENU_START;
            displaySubMenu();
            lastInputTime = currentTime;
        }
        else if (dir == JOY_PRESS)
        {
            if (currentOption == MENU_BACK)
            {
                currentState = STATE_MAIN_MENU;
                currentOption = MENU_GREEN_TEA;
                displayMainMenu();
            }
            else if (currentOption == MENU_START)
            {
                int brewTime = (currentState == STATE_GREEN_TEA) ? 1 :
                               (currentState == STATE_BLACK_TEA) ? 1 :
                               customTime;
                startBrew(brewTime);
            }
            lastInputTime = currentTime;
        }
    }
    else if (currentState == STATE_RUNNING)
    {
        if (dir == JOY_PRESS && currentOption == MENU_STOP)
        {
            stopBrew();
            lastInputTime = currentTime;
        }
    }
}

void MenuService::startBrew(int timeInMinutes)
{
    brewDuration = timeInMinutes * 60000; // Convert minutes to milliseconds
    startTime = millis();
    digitalWrite(relayPin, HIGH); // Turn on the relay
    currentState = STATE_RUNNING;
    currentOption = MENU_STOP;
    displayProgress();
}

void MenuService::stopBrew()
{
    digitalWrite(relayPin, LOW); // Turn off the relay
    currentState = STATE_MAIN_MENU;
    currentOption = MENU_GREEN_TEA;
    displayMainMenu();
    // Optional: Add any cleanup code here
}
