#include "Itsy.h"
#include "ZSingleWireSerial.h"
#include "hal_gpio.h"
#include "SAMDEIC.h"
#include "CodalDmesg.h"
#include "JACDAC.h"
#include "JDProtocol.h"
#include "JDReliabilityTester.h"


Itsy bitsySpider;
ZSingleWireSerial sws(bitsySpider.io.a4, SERCOM0, 0, PINMUX_PA04D_SERCOM0_PAD0, 0);
JACDAC jacdac(bitsySpider.io.a4, sws);

JDProtocol protocol(jacdac);

JDReliabilityTester r(bitsySpider.io.a0);

void run_test()
{
    while(1)
    {
        r.start();

        fiber_sleep(10000);
    }
}

int main()
{
    bitsySpider.init();
    DMESG("HELLO!");
    protocol.add(r);
    jacdac.start();

    int state = 0;

    create_fiber(run_test);

    while(1)
    {
        state = !state;
        bitsySpider.io.led.setDigitalValue(state);
        bitsySpider.sleep(500);
    }
}
