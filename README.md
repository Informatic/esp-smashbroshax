esp-smashbroshax
================

Portable [smashbroshax](https://github.com/yellows8/3ds_smashbroshax) beacon
broadcaster based on $2 ESP8266 wifi-enabled SoC/module.

Right now it is mostly developed on (still pretty cheap) NodeMCU devboard.
(around $4 on aliexpress)


Building
--------

Software is based on [Sming](https://github.com/SmingHub/Sming), however for
proper 802.11 management frame injection `lib/` in SDK had to be downgraded
from 1.5.0 to 1.3.0 version. (as per [esp8266-injection-example issue](https://
github.com/pulkin/esp8266-injection-example/issues/1))

Some fancy web interface is planned in future.

Right now payload is statically converted from .pcap to C header file with
`prepare_payload.py` tool.

    python prepare_payload.py ../pcap_out/smashbros_gameotherv100_beaconhax.pcap > app/payload.h
    make flash

Button connected to GPIO0 on NodeMCU board will start broadcasting beacon
frames. Blue "TX" LED on ESP-12 module indicates transmission.


Notes
-----

So far I haven't been able to successfuly exploit my N3DS, but seems like a
problem with HB launcher itself. Whatever.
