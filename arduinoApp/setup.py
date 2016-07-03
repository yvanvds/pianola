#!/usr/bin/python

import ConfigParser
from subprocess import call

rebootNeeded = False
answer = raw_input("(Re)install python libraries? (y/n)")

if answer == 'y':
  rebootNeeded = True

  # install easy_install scripts
  call(["./ez_setup.py", ""])
  # install pip
  call(["easy_install", "pip"])
  #install python osc module 
  call(["pip", "install", "pyosc"])

  # reset mcu after boot (to enable the yun bridge)
  with open("/etc/rc.local", "w") as f:
    f.write("/mnt/sda/resetMCU\n")
    f.write("boot-complete-notify\n")
    f.write("exit 0\n")

# set the name for this robot
robotName = raw_input("Please enter this robot's name: ")

#the router address is needed to find out our IP
routerAddress = raw_input("What is the IP address of the router: ")

config = ConfigParser.SafeConfigParser()

config.add_section('robot options')
config.set('robot options', 'name', robotName)

config.add_section('network')
config.set('network', 'routeraddress', routerAddress)

with open('config.cfg', 'wb') as configfile:
  config.write(configfile)

if rebootNeeded:
  # a reboot is the best way to ensure everything works as it should
  answer = raw_input("Reboot now? (y/n)")
  if answer == 'y':
    call(["reboot", ""])

print("Done!\n")