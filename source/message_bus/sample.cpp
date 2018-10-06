#include "BrainPad.h"
#include "ZSingleWireSerial.h"
#include "JDProtocol.h"
#include "JDMessageBusDriver.h"

BrainPad bp;
JDProtocol protocol(bp.jacdac);

JDMessageBusDriver serialBus;

ZPin PA3(ID_PIN_SERIAL_RX, PA_3, PIN_CAPABILITY_AD); // debug io

void set_gpio(int state)
{
    PA3.setDigitalValue(state);
}

#define APP_ID 9008

void message_bus_evt(Event e)
{
    if (e.value == DEVICE_BUTTON_EVT_DOWN)
    {
        bp.io.ledGreen.setDigitalValue(1);
    }
    if (e.value == DEVICE_BUTTON_EVT_UP)
    {
        bp.io.ledGreen.setDigitalValue(0);
    }
}

void button_event(Event e)
{
    codal_dmesg("button event %d", e.value);
    if (e.value == DEVICE_BUTTON_EVT_DOWN)
    {
        Event(APP_ID, e.value);
    }
    if (e.value == DEVICE_BUTTON_EVT_UP)
    {
        Event(APP_ID, e.value);
    }
}

int main()
{
    bp.init();
    // bp.sws.setBaud(1000000);
    int state = 1;
    bp.messageBus.listen(bp.buttonUp.id, DEVICE_ID_ANY, button_event);
    bp.messageBus.listen(APP_ID, DEVICE_ID_ANY, message_bus_evt);
    serialBus.listen(APP_ID, DEVICE_ID_ANY);
    protocol.add(serialBus);
    protocol.start();

    while(1)
    {
        bp.io.ledRed.setDigitalValue(state);
        fiber_sleep(500);
        state = !state;
    }
}