#ifndef JOY_SERVICE_H
#define JOY_SERVICE_H

#include <Arduino.h>

#define JOY_DEADZONE 100

enum JoyDirection
{
    JOY_LEFT,
    JOY_RIGHT,
    JOY_UP,
    JOY_DOWN,
    JOY_NONE,
    JOY_PRESS
};

class JoyService
{
public:
    JoyService(uint8_t x_pin, uint8_t y_pin, uint8_t button_pin);

    void init();
    void calibrate();
    JoyDirection read();

private:
    uint8_t x_pin;
    uint8_t y_pin;
    uint8_t button_pin;

    int x_center;
    int y_center;
    int x_range;
    int y_range;

    int x_filtered;
    int y_filtered;
};

#endif // JOY_SERVICE_H
