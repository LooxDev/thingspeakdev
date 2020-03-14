# WeTakeWeb ThingSpeak Service Library

## Description

An Arduino library for the ThingSpeak Webservice to be used with an <EtherCard.h> supported network interface.

You can find tutorials and more documentation [here](https://arduino.wetakeweb.de/thingspeakdev).

## Installation

1. Navigate to the Releases page.
1. Download the latest release.
1. Extract the zip file
1. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## Requirements

This library depends on [GitHub-<EtherCard.h>-Library](https://github.com/njh/EtherCard). To use this library the user must download the required library.

## Features

- ### Inexpensive

     This library is used with simple and low-cost network interface called "Microchip ENC28J60". This library is free of cost and the only cost is of the sensors.

- ### Compatible

    ThingSpeakDev library is compatible with all network interfaced compatible with the <EtherCard.h> library.

- ### Function calls

    Basic functions to communicate with the ThingSpeak Webservice using HTTP Headers have been implemented in this library. There's no need to re-implement these functions from scratch. The user simply has to import the library in the project and can use any of its functions by just calling it.

- ### Give back

    The library is free, you don’t have to pay for anything.

## Functions

- Constructors
- set/getMacAdress
- set/getWaitTime
- wait()
- set/getNumFields
- getWriteAPIKey()
- set/getField
- isReady()
- sendData()

## Example

Examples include a "simple" Write Data Example. Receiving Data will be added in the future. You can find this and following examples from [Github-ThingSpeakDev-Library](https://github.com/adafruit/DHT-sensor-library/tree/master/examples).

```Cpp
#include "thingSpeakDev.h"

const char *myWriteAPIKey = "ABCDEFGHIFKLPMNO";
ThingSpeakDev tsd;

void setup()
{
  Serial.begin(57600);
  Serial.println("Starting");
  tsd = ThingSpeakDev(myWriteAPIKey, 7, 15);
  while (!tsd.isReady())
  {
    Serial.println("Ceration of TSD failed");
    delay(5000);
  }
  byte macaddr[6] = {0x42, 0x31, 0x20, 0x64, 0x31, 0x16};
  tsd.setMacAdress(macaddr);
  Serial.println("Ready");
}

void loop()
{

  if (!tsd.wait())
  {
    float test = 42;

    tsd.setField(7, test);

    tsd.sendData();
  }
}
```

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this library
- Contribute new protocols
- Come up with a good name ;)

The best way to ask for help or propose a new idea is to [create a new issue](https://github.com/jmonska/thingspeakdev/issues/new).

## Credits

The author and maintainer of this library is WeTakeWeb <info@wetakeweb.de>

## License

This library is licensed under [GNU General Public License v3.0](https://github.com/jmonska/thingspeakdev/blob/master/LICENSE).
