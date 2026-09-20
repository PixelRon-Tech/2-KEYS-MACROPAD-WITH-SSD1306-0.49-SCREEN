# 2-KEYS-MACROPAD-WITH-SSD1306-0.49-SCREEN

A small macropad featuring two mechanical keys and a tiny OLED screen. It can be used for games such as **Geometry Dash** and **osu!**

## Features

* 2 mechanical keys
* 0.49" SSD1306 OLED display
* RP2040-Zero microcontroller
* Custom 3D-printed case and keycaps
* QMK firmware support
* Fully customizable key bindings and pin layout
* CUSTOM BINDING AND MACROS VIA BROWSER APP

## Components

* **RP2040-Zero**
* **SSD1306 0.49" OLED screen**
* **2× Brown Cherry MX-style switches (or any others but not hall effect one)**
* Custom-made keycaps and case (3D printed)
* 4x M3X13 Allen Socket Head Screws

## Pinout

### OLED Display

| Display Pin | RP2040-Zero       |
| ----------- | ----------------- |
| SDA         | GP4               |
| SCL         | GP5               |
| VDD         | 3.3V ⚠️ IMPORTANT |
| GND         | GND               |

### Keys

| Component     | RP2040-Zero |
| ------------- | ----------- |
| Key 1         | GP6         |
| Key 2         | GP7         |
| Common ground | GND         |

**Important:** Make sure the display is powered from **3.3V**, not 5V.

## Pictures

### Macropad

![Macropad](https://github.com/PixelRon-Tech/2-KEYS-MACROPAD-WITH-SSD1306-0.49-SCREEN/blob/9cfb7bfda4ade4c2f9c19727545a4a5cb02de8e3/Macropad.jpg)

### Macropad — Another View

![Macropad1](https://github.com/PixelRon-Tech/2-KEYS-MACROPAD-WITH-SSD1306-0.49-SCREEN/blob/9cfb7bfda4ade4c2f9c19727545a4a5cb02de8e3/Macropad1.jpg)

### Display Work

![DisplayWork](https://github.com/PixelRon-Tech/2-KEYS-MACROPAD-WITH-SSD1306-0.49-SCREEN/blob/9cfb7bfda4ade4c2f9c19727545a4a5cb02de8e3/DisplayWork.jpg)

## Setup

There are two ways to get the macropad working.

### 1. Flash the Precompiled Firmware

If you just want to use the macropad without changing anything:

1. Download the `.uf2` firmware file from this repository.
2. Connect your RP2040-Zero in bootloader mode.
3. Drag and drop the `.uf2` file onto the RP2040-Zero drive.
4. Connect the display and keys according to the pinout above.
5. If you want to use VIA binding app you will need to put "minipad.json" in to Design Tab (Method 2, Step 9 to 11)

**Make sure all connections are correct, or the macropad may not work properly.**

### 2. Compile Your Own QMK Firmware

If you want to change components, you can modify the firmware in the `minipad` folder.

#### Requirements

* QMK Firmware environment
* RP2040-Zero
* The `minipad` keyboard folder from this repository

#### Installation

1. Set up the [QMK Firmware environment](https://docs.qmk.fm/newbs).

2. Copy the `minipad` folder from this repository into:

   ```text
   qmk_firmware/keyboards/
   ```

3. Open **QMK MSYS** (QMK command-line environment).

4. Compile the firmware using:

   ```bash
   qmk compile -kb minipad -km via
   ```
*OR
   ```bash
   qmk compile -kb minipad -km default
   ```
*If you don't want to make binds from the app if you dont want to deal with "minipad.json" (Step 9)

5. Wait for the compilation to finish.

6. You should get a `.uf2` firmware file in your QMK firmware directory.

7. Connect your RP2040-Zero in bootloader mode.

8. Drag and drop the `.uf2` file onto the RP2040-Zero drive.

9. If you want to setup keybinds you will need to enter official VIA site (https://www.usevia.app/)

10. Enter "Design Tab" and past "minipad.json" from minipad folder in to this site.

11. Then plug in macropad, choose device from pop-up window.
 
And you're ready to go!

## 3D-Printed Case

You can also print the case included in this repository.

* The case and keycaps are custom-designed for this macropad.
* Some parts may need a little sanding.
* After sanding, the parts should fit together properly.
* Its also has an enclosure that used to tilt the macropad and hide the seams
* ⚠️ IMPORTANT: If you will use enclosure you will be not able to gently remove macropad from it.
  
## Firmware

This project uses **QMK Firmware**.

The firmware was written with the help of AI. It might not be the cleanest code, but it works, and I'm happy with it :)

Feel free to modify it and make it your own!
