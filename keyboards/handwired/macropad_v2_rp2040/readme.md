# macropad_v2_rp2040

![macropad_v2_rp2040](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Hoang Nguyen](https://github.com/isoamyl50)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make macropad_v2_rp2040:default

Flashing example for this keyboard:

    make macropad_v2_rp2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the rotary encoder button and plug in the keyboard (or short GPx pin with ground) while plugging the board in.
* **Double tap reset**: Press the RESET button (or short the RUN pin with ground) twice, quickly (less than 200 miliseconds between each press).
* **The BOOTSEL button**: Hold down the BOOTSEL button on the microcontroller board (or short the corresponding pin with ground) while plugging the board in.
