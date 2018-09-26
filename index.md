# JACDAC: Joint Asynchronous Communications, Device Agnostic Control.

## What is JACDAC?

JACDAC is a single wire serial protocol for the plug and play of accessories for embedded computers.

## Why do we need _another_ protocol?

Conventionally SPI and I2C are used to communicate with other devices over a wire. I2C and SPI principally work in Central/Peripheral (used in place of outdated Master/Slave terminology) mode: One central directs the operation of all peripherals, configuring and interrogating them as desired.

I2C uses static addresses for all components i.e. all MMA8653 accelerometers will have the same address. Each I2C component specifies its own register map and registers can be directly accessed by combining the component's address and register offset. I2C requires two wires to operate: _SCL_ to synchronise the communication speed, and _SDA_ for data payloads.

Instead of static addressing, SPI uses the peripheral select wire to indicate the peripheral to be accessed. SPI components require register offsets to be communicated over the MOSI (Central out peripheral in) line, and the selected peripheral responds using the MISO (Central in peripheral out) line. Multi-central modes for SPI and I2C are not well-supported.

Peer-to-peer scenarios are common place in the world of the Internet of Things (IoT): programmers often want to share data with other devices in the vicinity. But what solution is available for sharing data locally through wired communications? I2C or SPI cannot be used because of their communication topology (single Central only) and addressing approaches––if you connected two devices with the same components through joining buses, how are addresses resolved? Alternatively one could develop a custom UART based protocol from scratch, or, one could add ethernet capabilities to a device and run IPv4, requiring extra hardware and consuming precious RAM.

JACDAC requires _no additional hardware to operate_ as it is built on UART, supported in hardware by all modern processors. Peer to peer scenarios are supported through a _broadcast topology_ where every device is a Central. Only _a single wire_ is required as communications are fixed to 1 mBaud.

## A broadcast paradigm

![image of devices in a broadcast formation](images/bus.svg)