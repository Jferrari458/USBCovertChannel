from os.path import exists
from time import sleep
import usb.core
import usb.util
import argparse
import sys


# Initialization of argparse
parser = argparse.ArgumentParser()
parser.add_argument('-s', metavar='VID:PID', type=str, help='Set the VID and PID')
parser.add_argument('String', metavar='message', type=str, help='the message to be written')
args = parser.parse_args()

# Set usb.conf
if args.s:
    with open('usb.conf', 'w+') as file:
        file.write("VID:"+args.s.split(':')[0]+'\n')
        file.write("PID:"+args.s.split(':')[1]+'\n')
        print('Configuration saved')
        sleep(1)

# Get VID and PID
if exists('usb.conf'):
    with open('usb.conf', 'r') as file:
        vid = '0x'+file.readline().split(':')[1].strip('\n')
        pid = '0x'+file.readline().split(':')[1].strip('\n')
else:
    sys.stderr.write('Error: usb.conf not found\nPlease set VID and PID\n')
    sys.exit()

# find our device
vid = int(vid, 16)
pid = int(pid, 16)
dev = usb.core.find(idVendor=vid, idProduct=pid)

# was it found?
if dev is None:
    raise ValueError('Device not found')

# check for kernel driver attachment
if dev.is_kernel_driver_active(0):
    try:
        dev.detach_kernel_driver(0)
        print("kernel driver detached")
        sleep(1)
    except usb.core.USBError as e:
        sys.exit("could not detach kernel driver: ")
else:
    print("no kernel driver attached")
    sleep(1)

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
msg = dev.write(1, args.String, 100)
if msg:
    print('data written')

#dev.ctrl_transfer(0x00, 9, 1, 0, "testing")
