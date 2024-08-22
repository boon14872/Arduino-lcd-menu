#include "joy_service.h"
#include <LiquidCrystal_I2C.h>
#include "character.h"
class MenuService
{
private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
    JoyService joy = JoyService(A0, A1, A2);

    String menu_name;

    int menu_page_curr;
    int menu_page_prev;
    int menu_page_total;
    JoyDirection button_type;
    int animation_speed;
    int button_delay;

public:
    MenuService()
    {
        menu_name = "Main Menu";
        menu_page_curr = 1;
        menu_page_prev = 1;
        menu_page_total = 4;
        button_type = JOY_NONE;
        animation_speed = 250;
        button_delay = 250;
        initializeCharacters();
    }

    void initChars()
    {
        lcd.createChar(0, chr_arrowleft);
        lcd.createChar(1, chr_arrowright);
        lcd.createChar(2, chr_arrowup);
        lcd.createChar(3, chr_arrowdown);
        lcd.createChar(4, chr_slash);
        lcd.createChar(5, chr_indleft);
        lcd.createChar(6, chr_indright);
        lcd.createChar(7, chr_plus);
        lcd.createChar(8, chr_minus);
    }

    void initLCD()
    {
        lcd.init();
        lcd.backlight();
        lcd.clear();

        initChars();
        printStr(menu_name, 0, 0);
    }

    void printStr(String text, int index, int line)
    {
        if (text.length() > 16)
        {
            lcd.setCursor(0, 0);
            lcd.print(text);
            lcd.setCursor(0, 1);
            lcd.print(text.substring(17, text.length()));
        }
        else
        {
            lcd.setCursor(index, line);
            lcd.print(text);
        }
    }

    void printChr(int character, int index, int line)
    {
        lcd.setCursor(index, line);
        lcd.write(character);
    }

    void clearLine(int line)
    {
        lcd.setCursor(0, line);
        lcd.print("                ");
    }

    void loadingAnimation(String text)
    {
        int text_length = text.length();

        if (text_length > 13)
        {
            printStr(String("Loading"), 0, 1);
            delay(animation_speed * 4);
        }
        else
        {
            while (true)
            {
                printStr(text, 0, 1);
                delay(animation_speed);

                printStr(text, 0, 1);
                printStr(String("."), text_length, 1);
                delay(animation_speed);

                printStr(text, 0, 1);
                printStr(String(".."), text_length, 1);
                delay(animation_speed);

                printStr(text, 0, 1);
                printStr(String("..."), text_length, 1);
                delay(animation_speed);

                clearLine(1);
                break;
            }
        }
    }

    void printMenu()
    {
        clearLine(1);
        printChr(2, 13, 1);
        printChr(4, 14, 1);
        printChr(3, 15, 1);
        switch (menu_page_curr)
        {
        case 1:
            printStr(menu_feature[0][0], 0, 1);
            break;
        case 2:
            printStr(menu_feature[1][0], 0, 1);
            break;
        case 3:
            printStr(menu_feature[2][0], 0, 1);
            break;
        case 4:
            printStr(menu_feature[3][0], 0, 1);
            break;
        }
    }

    void printFeatures()
    {
        clearLine(1);
        printChr(8, 15, 1);
        switch (menu_page_curr)
        {
        case 1:
            printStr(menu_feature[0][1], 0, 1);
            break;
        case 2:
            printStr(menu_feature[1][1], 0, 1);
            break;
        case 3:
            printStr(menu_feature[2][1], 0, 1);
            break;
        case 4:
            printStr(menu_feature[3][1], 0, 1);
            break;
        }
    }

    void menuLogic()
    {
        Serial.print("Button: ");
        Serial.println(button_type);
        switch (button_type)
        {
        case JOY_DOWN:
            menu_page_curr = (menu_page_curr % menu_page_total) + 1;
            delay(button_delay);
            break;
        case JOY_UP:
            menu_page_curr = (menu_page_curr - 2 + menu_page_total) % menu_page_total + 1;
            delay(button_delay);
            break;
        case JOY_LEFT:
            printStr(button_name[0], 0, 1);
            delay(button_delay);
            break;
        case JOY_RIGHT:
            printStr(button_name[1], 0, 1);
            delay(button_delay);
            break;
        default:
            if (button_type == JOY_PRESS)
            {
                printFeatures();
                delay(button_delay);
            }
            break;
        }

        if (menu_page_curr != menu_page_prev)
        {
            printMenu();
            menu_page_prev = menu_page_curr;
        }
    }

    void setup()
    {
        initLCD();
        joy.init();
        loadingAnimation(String("Setup"));
        printMenu();
    }

    void loop()
    {
        button_type = joy.read();
        menuLogic();
    }
};
