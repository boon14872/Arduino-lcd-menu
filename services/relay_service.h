// relay service for controlling the relay

class RelayService
{
private:
    int relay_pin;
    bool relay_state;

public:
    RelayService(int pin)
    {
        relay_pin = pin;
        relay_state = false;
        pinMode(relay_pin, OUTPUT);
        digitalWrite(relay_pin, LOW);
    }

    void toggleRelay()
    {
        relay_state = !relay_state;
        digitalWrite(relay_pin, relay_state);
    }

    void setRelay(bool state)
    {
        relay_state = state;
        digitalWrite(relay_pin, relay_state);
    }

    bool getRelayState()
    {
        return relay_state;
    }
};
