# Raspberry Pi Pico MacroPad

### Description
This MacroPad uses the bottom four buttons to select a mode/page.
Each mode then provides a different function for each of the other 12 buttons.
In total, this provides 36 fully customisable buttons.
The current code does not allow you to press a sequence of buttons, but does allow a combination of buttons to be pressed together.
Currently only 5 buttons have been given any functionality.

### How to Build
- Navigate to the directory.
- Create a build directory: `mkdir build`
- Navigate to that build directory: `cd build`
- Run cmake on the parent directory: `cmake ..`
- Run make: `make`

This will generate a bunch of files, you will want to drag the `macro_pad.uf2` files from the folder `build/macro_pad`.

### Products
Buy a Raspberry Pi Pico [here](https://thepihut.com/products/raspberry-pi-pico).
Buy the 4x4 RGB Keypad [here](https://shop.pimoroni.com/products/pico-rgb-keypad-base).

### Libraries
[Pico SDK (includes TinyUSB)](https://github.com/raspberrypi/pico-sdk)
[Pimoroni Pico](https://github.com/pimoroni/pimoroni-pico/)