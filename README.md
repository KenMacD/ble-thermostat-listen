# BLE Thermometer Listener

Very simple listener for BLE Advertisments from Xiaomi Thermometers
that are then forwarded over USB.

## Useful Commands

* Build: `west build`
* Flash with bootloader: `west flash -r pyocd`
* Flash over USB: `~/go/bin/mcumgr --conntype serial --connstring "/dev/ttyACM0,baud=115200" image upload ./build/zephyr/app_update.bin`

## TODO

* USB VID info seems ignored in mcuboot
* Do something with RGB led
* Sign image
