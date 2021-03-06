#include "BrainPad.h"
#include "ZSingleWireSerial.h"
#include "JDProtocol.h"
#include "JDPinDriver.h"

BrainPad bp;
JDProtocol protocol(bp.jacdac);
ZPin PA3(DEVICE_ID_IO_P0 + 40, PA_3, PIN_CAPABILITY_ALL);

JDPinDriver pin;

int extState = 0;
void on_button_pressed(Event)
{
    extState = !extState;
    pin.setDigitalValue(extState);
}

void on_paired(Event)
{
    bp.io.ledGreen.setDigitalValue(1);
}

void on_unpaired(Event)
{
    bp.io.ledGreen.setDigitalValue(0);
}

int main()
{
    bp.init();

    bp.messageBus.listen(bp.buttonUp.id, DEVICE_BUTTON_EVT_CLICK, on_button_pressed);

    bp.messageBus.listen(pin.id, JD_DRIVER_EVT_PAIRED, on_paired);
    bp.messageBus.listen(pin.id, JD_DRIVER_EVT_UNPAIRED, on_unpaired);

    int state = 1;
    protocol.add(pin);
    jacdac.start();

    while(1)
    {
        bp.io.ledRed.setDigitalValue(state);
        fiber_sleep(500);
        state = !state;
    }
}
