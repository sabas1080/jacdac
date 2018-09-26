# JACDAC: Joint Asynchronous Communications, Device Agnostic Control.

## What is JACDAC?

JACDAC is a single wire serial protocol for the plug and play of accessories for embedded computers.

## Why do we need _another_ protocol?

Conventionally SPI and I2C are used to communicate with other devices over a wire. I2C and SPI principally work in Central/Peripheral (used in place of outdated Master/Slave terminology) mode: One central directs the operation of all peripherals, configuring and interrogating them as desired.

I2C uses static addresses for all components i.e. all MMA8653 accelerometers will have the same address. Each I2C component specifies its own register map and registers can be directly accessed by combining the component's address and register offset. I2C requires two wires to operate: _SCL_ to synchronise the communication speed, and _SDA_ for data payloads.

Instead of static addressing, SPI uses the peripheral select wire to indicate the peripheral to be accessed. SPI components require register offsets to be communicated over the MOSI (Central out peripheral in) line, and the selected peripheral responds using the MISO (Central in peripheral out) line. Multi-central modes for SPI and I2C are not well-supported.

However, in the world of the Internet of Things (IoT), peer-to-peer scenarios are common place: programmers often want to share data with other devices in the vicinity. But what solution is available for sharing data locally through wired communications? I2C or SPI cannot be used because of their addressing approaches and communication topology (single Central only)––if two devices with the same components join buses, how are addresses resolved? One could develop a custom UART based protocol from scratch requiring the design of an entire protocol stack, or one could add ethernet capabilities to a device and run IPv4, requiring extra hardware and consuming precious RAM.

Built on UART, JACDAC requires _no additional hardware to operate_ as UART is supported in hardware by all modern processors. Peer to peer scenarios are enabled through a _broadcast topology_ where every device is a Central. Communications speeds are fixed to 1 mBaud, which means only _a single data wire_ is required.

## A broadcast paradigm

![image of devices in a broadcast formation](images/bus.svg)