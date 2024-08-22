#ifndef JOY_SERVICE_H
#define JOY_SERVICE_H

#define JOY_DEADZONE 30

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
    JoyService(uint8_t x_pin, uint8_t y_pin, uint8_t button_pin) : x_pin(x_pin), y_pin(y_pin), button_pin(button_pin) {}

    void init();
    JoyDirection read();

private:
    uint8_t x_pin;
    uint8_t y_pin;
    uint8_t button_pin;

    // Calibration values
    int x_center;
    int y_center;
    int x_range;
    int y_range;

    // Filter variables
    int x_filtered;
    int y_filtered;
};

void JoyService::init()
{
    pinMode(x_pin, INPUT);
    pinMode(y_pin, INPUT);
    pinMode(button_pin, INPUT);

    // Calibrate joystick
    x_center = 512;
    y_center = 512;
    x_range = 200; // Corresponds to ±100 range
    y_range = 200; // Corresponds to ±100 range

    // Initialize filter values
    x_filtered = x_center;
    y_filtered = y_center;
}

JoyDirection JoyService::read()
{
    int x = analogRead(x_pin);
    Serial.print(x);
    Serial.print(" ");

    int y = analogRead(y_pin);
    Serial.println(y);

    bool button = digitalRead(button_pin);
    Serial.print("button: ");

    Serial.println(digitalRead(button_pin));

    // Filter readings
    x_filtered = (x_filtered * 9 + x) / 10; // Simple moving average filter
    y_filtered = (y_filtered * 9 + y) / 10;

    Serial.print("button: ");
    Serial.println(button);
    if (button == 1)
    {
        return JOY_PRESS;
    }

    // Apply dead zone
    if (abs(x_filtered - x_center) < JOY_DEADZONE && abs(y_filtered - y_center) < JOY_DEADZONE)
    {
        return JOY_NONE;
    }

    // Determine direction based on calibrated values
    if (x_filtered < x_center - x_range / 2)
    {
        return JOY_LEFT;
    }
    else if (x_filtered > x_center + x_range / 2)
    {
        return JOY_RIGHT;
    }
    else if (y_filtered < y_center - y_range / 2)
    {
        return JOY_DOWN;
    }
    else if (y_filtered > y_center + y_range / 2)
    {
        return JOY_UP;
    }

    return JOY_NONE; // Should not happen with proper calibration
}

#endif // JOY_SERVICE_H
