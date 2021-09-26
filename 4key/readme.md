# 3-Key-Ecosystem - 4key devices (4key1, 4key2)

![4key devices](https://i.imgur.com/s1vaNye.jpg)

This is a 2x2 macro keyboard.
It's designed for a modular keyboard mount using an ATmega32U4.
There are two versions: 4key1 (uses individual LEDs), and 4key2 (uses WS2812B LEDs).

* Keyboard Maintainer: [softplus](https://github.com/softplus)
* Hardware Supported: [3keyecosystem-4key1](https://github.com/softplus/3keyecosystem/tree/main/4key/4key1) and [4key2](https://github.com/softplus/3keyecosystem/tree/main/4key/4key2)
* Hardware Availability: Open-Source files at above link

Make example for this keyboard (after setting up your build environment):

    make 3keyecosystem/4key/4key2:default

Flashing example for this keyboard:

    make 3keyecosystem/4key/4key2:default:flash

## Bootloader

To Enter the bootloader, click reset button on the main board.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
