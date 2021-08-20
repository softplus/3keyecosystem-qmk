# 3-Key-Ecosystem - kai6

![keyboard](https://i.imgur.com/IJ1Zyc7.jpeg)

This is 3x2 macro keyboard using an ATmega32U4, with a hand-solderable PCB.
It's designed by John Mueller.

* Keyboard Maintainer: [softplus](https://github.com/softplus)
* Hardware Supported: [kai6](https://github.com/softplus/3keyecosystem/tree/main/one-offs/kai6)
* Hardware Availability: Open-Source files at above link

Make example for this keyboard (after setting up your build environment):

    make 3keyecosystem/kai6:default

or flash it (requires hitting the reset button on the main board):

    make 3keyecosystem/kai6:default:flash

## Bootloader

To Enter the bootloader, click reset button on the main board.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
