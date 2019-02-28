import random

class JDBus:
    def __init__(self, buses = None):
        self.devices = []
        if buses is not None:
            for b in buses:
                self.devices += b.devices
        self.moves = 0

    def addDevice(self, device):
        self.devices += [device]

class JDDevice:
    JD_DEVICE_STATE_UNITIALISED = 0
    JD_DEVICE_STATE_PROPOSING = 1
    JD_DEVICE_STATE_ALLOCATED = 2
    def __generate_unique_addr(self, bus_addresses):
        addr = random.randint(1, 255)
        done = False
        while not done:
            if addr in bus_addresses:
                addr = random.randint(1, 255)
            else:
                break
        return addr

    def __init__(self, existing):
        self.count = 0
        self.address = random.randint(1, 255)

        allocated = random.randint(0, 1)
        if allocated == 0:
            existing_addresses = [d.address for d in existing if d.state == d.JD_DEVICE_STATE_ALLOCATED]
            self.address = self.__generate_unique_addr(existing_addresses)
            self.state = self.JD_DEVICE_STATE_ALLOCATED
        else:
            self.state = self.JD_DEVICE_STATE_UNITIALISED

    def reinit(self, bus_addresses = None):
        self.count = 0
        # if given bus_addresses we can better pick a next best guess
        if bus_addresses is None:
            self.address = random.randint(1, 255)
        else:
            self.address = self.__generate_unique_addr(bus_addresses)

        self.state = self.JD_DEVICE_STATE_PROPOSING

def handle_addresses(buses):
    done = False
    print ("Allocating/resolving addresses")
    while not done:
        done = True
        for b in buses:
            bus_addresses = [d.address for d in b.devices if d.state == d.JD_DEVICE_STATE_ALLOCATED]
            # bus_addresses = []
            for device in b.devices:
                if device.state == device.JD_DEVICE_STATE_UNITIALISED:
                    device.count = 0
                    device.state = device.JD_DEVICE_STATE_PROPOSING

                elif device.state == device.JD_DEVICE_STATE_PROPOSING:
                    device.count += 1

                    if device.count == 3:
                        device.state = device.JD_DEVICE_STATE_ALLOCATED

            for d1 in b.devices:
                for d2 in b.devices:
                    if d1 == d2:
                        continue

                    if d1.address == d2.address:
                        done = False
                        order = random.randint(0,1)

                        if order and d1.state != d1.JD_DEVICE_STATE_ALLOCATED:
                            d1.reinit(bus_addresses)
                        else:
                            d2.reinit(bus_addresses)

                        b.moves += 1

                if d1.state == d1.JD_DEVICE_STATE_PROPOSING:
                    done = False

ask_for_input = False

if ask_for_input:
    bus_count = int(input("Enter the number of buses:"))
    devices_per_bus = int(input("Enter the number of devices per bus:"))
else:
    bus_count = 2
    devices_per_bus = 120

# create buses
buses = []
for i in range(0,bus_count):
    buses += [JDBus()]

# allocate devices
for b in buses:
    for i in range(0,devices_per_bus):
        b.addDevice(JDDevice(b.devices))


# allocate addresses
handle_addresses(buses)

for i in range(0,bus_count):
    print ("Bus %d allocation of addresses took %d moves" % (i + 1, buses[i].moves))

if bus_count * devices_per_bus > 254:
    print("cannot merge buses, total device count is greater than the maximum supported device amount (254)")
    exit()

print("merging buses")

merged_bus = JDBus(buses)
handle_addresses([merged_bus])

print ("Merging of buses took %d moves" % ( buses[i].moves))
