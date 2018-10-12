#include "BrainPad.h"
#include "ZSingleWireSerial.h"
#include "JDProtocol.h"
#include "JDReliabilityTester.h"

BrainPad bp;
JDProtocol protocol(bp.jacdac);
ZPin PA3(DEVICE_ID_IO_P0 + 40, PA_3, PIN_CAPABILITY_ALL);

// JDPinDriver p(PA3);
JDReliabilityTester r;

void set_gpio(int)
{

}

int extState = 0;
void on_button_pressed(Event)
{
    bp.io.ledGreen.setDigitalValue(0);
    bp.io.ledBlue.setDigitalValue(0);

    int ret = r.start();

    if (ret == 100)
        bp.io.ledGreen.setDigitalValue(1);
    else
        bp.io.ledBlue.setDigitalValue(1);
}

int main()
{
    bp.init();

    bp.messageBus.listen(bp.buttonUp.id, DEVICE_BUTTON_EVT_CLICK, on_button_pressed);

    int state = 1;
    protocol.add(r);
    jacdac.start();

    while(1)
    {
        bp.io.ledRed.setDigitalValue(state);
        fiber_sleep(500);
        state = !state;
    }
}
