# Extra Text

JACDAC device HostServices

_____

Ideally all JACDAC peripherals should run at 1Mbaud, but this baud rate is only supported on expensive MCUs which are not necessary in all scenarios. Take for example a JACDAC button peripheral, all that needs to be communicated is the state of the button (1 byte) and a control packet (12 bytes); using a $1.50 MCU to do this is extreme.

# How does addressing actually work?

After the description of driver modes it might not be clear how addresses are used in JACDAC, this section provides formalisation.

## Virtual Mode

![virtual mode addressing](images/addressing-virtual.svg)

## Paired Mode

![paired mode addressing](images/addressing-paired.svg)


## Broadcast Mode

![broadcast mode addressing](images/addressing-broadcast.svg)

__Need to solidify addressing, it's currently not clear how it all fits together... need to write about the fact that because packets are received by a host driver using its own address it can infer that the packet came externally, addressing diagrams might be useful__

For reliable communications, embedded programmers tend to stay clear of UART: there is no common clock, the baud rate must be pre-determined, and there is no bus arbitration on the reception and transmission lines. Fortunately, hardware has improved over time adding DMA buffering and auto-baud detection thus improving reliability.

JACDAC uses the built-in UART module common to most MCUs as its communication mechanism, but instead of running two separate wires for transmission and reception, JACDAC uses just one wire for both in a bus topology.

JACDAC supports four baud rates: 1Mbaud, 500Kbaud, 250Kbaud, 125Kbaud, allowing cheaper MCUs to be used. By supporting multiple baud rates, JACDAC enables low cost MCUs to be used in JACDAC peripherals with small payloads, where the use of lower baud rates has minimal impact on the throughput of the bus.

This approach allows devices to listen to the bus in a low power mode using a GPIO interrupt, enabling UART hardware only when required. As with traditional UART, when no device is transmitting the bus floats high.