#include "MenuService.h"

MenuService::MenuService(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows, uint8_t joyXPin, uint8_t joyYPin, uint8_t joyButtonPin, uint8_t relayPin) 
    : lcd(lcdAddr, lcdCols, lcdRows), joy(joyXPin, joyYPin, joyButtonPin), relayPin(relayPin), currentState(STATE_MAIN_MENU), currentOption(MENU_GREEN_TEA), customTemperature(75), customTime(3), startTime(0), brewDuration(0), debounceDelay(1000), lastInputTime(0)
{
}

void MenuService::init()
{
    lcd.init();
    lcd.backlight();
    joy.init();
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);

    displayMainMenu();
}

void MenuService::update()
{
    handleInput();

    if (currentState == STATE_RUNNING)
    {
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
        lcd.print("Custom: ");
        lcd.print(customTime);
        lcd.print(" min");
        break;
    default:
        break;
    }

    lcd.setCursor(0, 1);
    if (currentState == STATE_CUSTOM && currentOption == MENU_SET_TIME)
    {
        lcd.print("> Set Time");
    }
    else if (currentOption == MENU_START)
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

void MenuService::displaySetTime()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Time: ");
    lcd.setCursor(0, 1);
    lcd.print(customTime);
    lcd.print(" min");
}
void MenuService::displayProgress()
{
    static unsigned long lastDisplayTime = 0;
    unsigned long currentTime = millis();

    if (currentTime - lastDisplayTime >= 200)
    {
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
}

void MenuService::handleInput()
{
    unsigned long currentTime = millis();

    if (currentTime - lastInputTime < debounceDelay)
    {
        return;
    }

    JoyDirection dir = joy.read();
    Serial.println(dir);



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
                currentOption = MENU_SET_TIME;
                displaySubMenu();
                break;
            default:
                break;
            }
            lastInputTime = currentTime;
        }
    }
    else if (currentState == STATE_CUSTOM)
    {
        if (currentOption == MENU_SET_TIME)
        {
            if (dir == JOY_UP)
            {
                customTime++;
                displaySetTime();
                lastInputTime = currentTime;
            }
            else if (dir == JOY_DOWN)
            {
                customTime--;
                if (customTime < 1) customTime = 1;
                displaySetTime();
                lastInputTime = currentTime;
            }
            else if (dir == JOY_PRESS)
            {
                currentOption = MENU_START;
                displaySubMenu();
                lastInputTime = currentTime;
            }
        }
        else if (currentOption == MENU_START || currentOption == MENU_BACK)
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
                    startBrew(customTime);
                }
                lastInputTime = currentTime;
            }
        }
    }
    else if (currentState == STATE_GREEN_TEA || currentState == STATE_BLACK_TEA)
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
                int brewTime = (currentState == STATE_GREEN_TEA) ? GREEN_TEA_TIME : BLACK_TEA_TIME;
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
    brewDuration = timeInMinutes * 60000;
    startTime = millis();
    digitalWrite(relayPin, HIGH);
    currentState = STATE_RUNNING;
    currentOption = MENU_STOP;
    displayProgress();
}

void MenuService::stopBrew()
{
    digitalWrite(relayPin, LOW);
    currentState = STATE_MAIN_MENU;
    currentOption = MENU_GREEN_TEA;
    displayMainMenu();
}
