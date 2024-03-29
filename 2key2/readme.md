# 3-Key-Ecosystem - 2key devices (2key1, 2key2)

![2key2 macro keyboard](https://i.imgur.com/IJ1Zyc7.jpeg)

This is a 2x1 macro keyboard.
It's designed for a modular keyboard mount using an ATmega32U4.

* Keyboard Maintainer: [softplus](https://github.com/softplus)
* Hardware Supported: [3keyecosystem-2key2](https://github.com/softplus/3keyecosystem/tree/main/2key/2key2)
* Hardware Availability: Open-Source files at above link

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb 3keyecosystem/2key2 -km default

Flashing example for this keyboard:

    qmk flash -kb 3keyecosystem/2key2 -km default

## Bootloader

To Enter the bootloader, click reset button on the main board.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
