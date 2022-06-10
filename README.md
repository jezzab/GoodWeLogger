# GoodWe Solar inverter logger based on ESP32

This ESP32 firmware enables you to read information from a [GoodWe](https://www.goodwe.com/?l=en-us) solar inverter through it's RS485 bus.  
Sending information to a MQTT broker is supported, as well as uploading information to [PVOutput](https://pvoutput.org/about.html).

## Requirements
  - GoodWe inverter with a RS485 connector (this software has been tested with GW3000-NS, GW3600D-NS, GW10KN-DT, but other inverters might also work)
  - ESP32 module - DFRobot FireBeetle V2 was used (https://www.dfrobot.com/product-1590.html)
  - LiPo battery to match the above board
  - RS485 converter (can be found on sites like AliExpress, search for `SCM TTL to RS485 Adapter 485 to UART Serial Port 3.3V 5V Level Converter Module`). For example the *XY-017* board is suitable  
  - Computer with Arduino IDE installed to flash the firmware

## Flashing firmware
 - To flash this firmware, you will need to install the Arduino IDE and configure it for the board you are using (NodeMCU / WeMos)
 - You will also need the following libraries, placed into the `libraries` folder belonging to Arduino on your system:
   - ['Time' library](https://github.com/PaulStoffregen/Time)
   - [NTPClient](https://github.com/arduino-libraries/NTPClient)
   - [PubSubClient](https://github.com/knolleary/pubsubclient)
   - [RemoteDebug (forked)](https://github.com/jantenhove/RemoteDebug)
 - Clone/download this repository
 - Rename the `Settings.example.h` to `Settings.h` and configure it to match your preferred settings
 - Compile and upload the firmware to your ESP32 using the Arduino IDE  
 
 Diagnostics information is sent over serial at 115200 baud *(wifi status, MQTT status, inverter connection status)*

## Connecting hardware
The RS485 connector on the inverter is located at the bottom of the inverter, visible when you remove the original GoodWe wifi-module. It could also be hidden behind a small metal plate (for inverters without WiFi). 
It is a 6 pin green terminal (male), the female counterpart is probably part number CTB92HE/6 (3.81mm pitch) but this hasn't been confirmed yet. You can order the female counterpart on eBay/AliExpress/Farnell or similar sites. Using female-female jumper wires that you insert directly into the connector and ESP32 also works.

The LiPo battery will keep the power to the ESP32 board overnight as the inverter loses power. If you dont use the LiPo you will have issues with MQTT and it holding the last value and not resetting.

***Above information applies to the GWxxxxD-NS range of inverters. Other models might use a different method of connecting. Consult your inverter manual.***

The green 6 pin connector inside the inverter looks like this:

       +------------+    +---+---+---+---+---+---+
       |------------|    | . | . | . | . | . | . | 
       +------------+    +---+---+---+---+---+---+ 
            USB            1   2   3   4   5   6

### Connecting to the inverter

Inverter | RS485 converter
--- | ---
pin 1  *(485_TX-)* | A+
pin 2 *(485_TX+)* | B-

**Pay attention, RS485 will only work if you disconnect the WiFi module and restart the inverter. 
They cannot work simultaneously.**

### Connecting RS485 converter to ESP32

RS485 converter | ESP32
--- | ---
GND | G / GND
RXD | D2
TXD | D3
VCC | 5V / 3V3

*(`D1` (receive) and `D2` (transmit) can be configured to different pins in `Settings.h`)*. It might look weird to connect `RXD` of the module to the receive pin of the ESP32, but this is how the XY-017 RS485 converter is labeled.

### Powering ESP32 from the GoodWe inverter
Instead of supplying power to the ESP32 with a separate USB power adapter, it is also possible to 'steal' power from the GoodWe inverter. This can be done by tapping in to the white cable with 5 pin connector (JST-XH) that is normally connected to the original GoodWe wifi-module.

Use this method at your own risk, and measure/check first before attempting this method! See [here](https://github.com/jantenhove/GoodWeLogger/issues/25) for more information. Confirmed to be working with at least GW3000-NS. 

## Retrieving information via MQTT
Subscribe to the `goodwe/` topic in your MQTT client. Information will be posted there and will look like this:
```
goodwe/93600DVA295R148/vpv1 242.6
goodwe/93600DVA295R148/vpv2 235.7
goodwe/93600DVA295R148/ipv1 4.9
goodwe/93600DVA295R148/ipv2 5.5
goodwe/93600DVA295R148/vac1 240.6
goodwe/93600DVA295R148/iac1 10.7
goodwe/93600DVA295R148/fac1 49.99
goodwe/93600DVA295R148/pac 2582
goodwe/93600DVA295R148/temp 38.6
goodwe/93600DVA295R148/eday 6.40
goodwe/93600DVA295R148/workmode 1
goodwe/93600DVA295R148/online 1
```
Field | Description | Unit
--- | --- | ---
vpv1 | Voltage of first string of solarpanels | V
vpv2 | Voltage of second string of solarpanels | V
ipv1 | Current of first string of solarpanels | A
ipv2 | Current of second string of solarpanels | A
vac1 | Voltage mains side inverter | V
iac1 | Current mains side inverter | A
fac1 | Frequency mains side inverter | Hz
pac | Current power production in Watt | W
temp | Internal temperature of inverter | &deg;C
eday | Energy produced today | kWh
workmode | Undocumented parameter. Default=1 | binary
online | Inverter status (1=on, 0=off) | binary

## PVOutput
When you have your PVOutput *API key* and *System ID* configured correctly in `Settings.h`, production data from the inverter will be uploaded to PVOutput every 5 minutes *(interval is configurable in `Settings.h`, but don't go lower than the minimal interval of every 5 minutes as specified by PVOutput)*.
When multiple inverters are connected, by daisy-chaining the RS485 cable, be aware that only the production data of the first inverter will be uploaded!

For the PVOutput upload function to work, it is important that the ESP32 has access to the internet. 
Apart from connections being made to PVOutput, you will also see that the ESP32 talks with `pool.ntp.org` every hour. This is done to retrieve the current time, which is needed to post data to PVOutput.

If you plan to use only MQTT, internet access for the ESP32 is not needed.


## TODO
- Webpage to configure parameters that are now hardcoded in `Settings.h`
- Extract other parameters from inverter(s)
- Detect if inverter is single phase or three phase model
