#include "BLENano.h"
#include "codal_target_hal.h"
#include "JACDAC.h"
#include "JDProtocol.h"
#include "JDPinDriver.h"

BLENano nano;

JACDAC jacdac(nano.io.P30, nano.sws);
JDProtocol protocol(jacdac);

JDPinDriver pin(nano.io.P29);

void on_paired(Event)
{
    nano.io.P2.setDigitalValue(1);
}

void on_unpaired(Event)
{
    nano.io.P2.setDigitalValue(0);
}

int main()
{
    nano.init();
    protocol.add(pin);
    jacdac.start();

    nano.messageBus.listen(pin.id, JD_DRIVER_EVT_PAIRED, on_paired);
    nano.messageBus.listen(pin.id, JD_DRIVER_EVT_UNPAIRED, on_unpaired);

    int state = 1;

    while(1)
    {
        nano.sleep(500);
        nano.io.led.setDigitalValue(state);
        state = !state;
    }

    release_fiber();
}