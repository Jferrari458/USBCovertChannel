import usb.core
import usb.util
import sys

# find our device
dev = usb.core.find(idVendor=0x1908, idProduct=0x1320)

# was it found?
if dev is None:
    raise ValueError('Device not found')

# check for kernel driver attachment
if dev.is_kernel_driver_active(0):
    try:
        dev.detach_kernel_driver(0)
        print("kernel driver detached")
    except usb.core.USBError as e:
        sys.exit("could not detach kernel driver: ")
else:
    print("no kernel driver attached")

# set the active configuration. With no arguments, the first
# configuration will be the active one
dev.set_configuration()

# get an endpoint instance
cfg = dev.get_active_configuration()
intf = cfg[(0,0)]

#ep = usb.util.find_descriptor(
#    intf,
#    # match the first OUT endpoint
#    custom_match = \
#    lambda e: \
#        usb.util.endpoint_direction(e.bEndpointAddress) == \
#        usb.util.ENDPOINT_OUT)

#assert ep is not None

# write the data
msg = dev.write(1, 'abcdefsecret', 100)
print(msg)

#dev.ctrl_transfer(0x00, 9, 1, 0, "testing")
