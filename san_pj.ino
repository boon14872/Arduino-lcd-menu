#include "services/menu_service.h"

MenuService myMenu;

void setup()
{
    Serial.begin(115200);
    myMenu.setup();
}

void loop()
{
    myMenu.loop();
}