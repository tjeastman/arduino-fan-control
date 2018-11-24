Control a four pin computer fan with a potentiometer and an Arduino.

First, download the [TM1637](https://github.com/avishorp/TM1637) library to drive the RPM display.
Place it into your libraries directory (likely `~/sketchbook/libraries`).

This project is based on [Arduino Makefile](https://github.com/sudar/Arduino-Makefile).
Run `make upload` to build and upload the firmware to the Arduino board.

pin color | function
--------- | --------
yellow | +12V
black | ground
blue | control
green | sense
