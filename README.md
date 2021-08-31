
If you like my job, you can support me by paying me a 🍺 or a ☕. Thanks 🙂

 [ ![Download](https://user-images.githubusercontent.com/12702322/115148445-e5a40100-a05f-11eb-8552-c1f5d4355987.png) ](https://www.paypal.me/CyrilGuislain)

<img align="left" width=600 src="https://user-images.githubusercontent.com/12702322/129816796-0f8a7844-0c04-45f5-aee3-321125e5ebe4.jpg" />


<br /><br /><br /><br /><br />

**Marlin 2.0.8 Firmware configured for FLSUN Super Racer with MKS Robin Nano V3 motherboard. Based on FLSUN sources.**

<br /> <br /> <br /> <br /> <br />

## Main features:

- MKS Robin Nano V3 motherboard support
- TMC2209 / TMC2226 UART drivers support
- Nozzle & Bed PID support
- Enabled thermal protection for Nozzle & Bed
- Bed Leveling Bilinear 9 x 9 point support
- Nozzle Park / Advanced Pause support with improved position
- Babystepping with Combine Z-Offset support
- EEPROM support
- S-Curve Acceleration support
- Bed Skew Compensation support (https://www.thingiverse.com/thing:2563185)
- G26 - Mesh Validation Pattern support
- G33 - Delta Auto Calibration support
- Enabled Hotend idle timeout (15 minutes)
- Disabled Power Loss Recovery by default. To avoid slowdowns at the end of each layer and preserve SD card / USB drive. (Enable it with `M413 S1` & `M500` in a terminal)
- Binary file transfert support to transfer and update the firmware remotely
- Enabled host prompt support
- Enabled Firmware Info with M115
- Enabled monitor for TMC drivers
- Enabled M106 to report the new fan speed when changed
- Improved probing speed
- Improved buffer size
- Fix TMC drivers settings
- Disabled not used settings

## Installation procedure:

- Do an EEPROM reset before flashing the new firmware (command `M502` followed by command `M500` in a terminal or with the TFT screen).
- Restart the printer.
- Choose version you want [here](https://github.com/Guilouz/Marlin-SuperRacer-MKS-Nano-V3/releases), `SDCARD` to use microSD Card port or `USB` to use USB port.
- Copy `Robin_nano_v3.bin` file to the root of the microSD card (max capacity 32GB, formatted in FAT32, allocation unit size 4096).
- With printer off, insert the microSD card into the dedicated port on the motherboard and turn on the printer.
- Flash procedure starts (without displaying anything on the screen) and lasts a few seconds.
- Check contents of the microSD card, `Robin_nano_v3.bin` file has been renamed to `ROBIN_NANO_V3.CUR` which indicates that the flash was successful.
- It's possible after flash you loose text on TFT screen, select your language again and save.
- Do an EEPROM reset again (command `M502` followed by command `M500` in a terminal or with the TFT screen).
- Restart the printer.
- Launch a Nozzle PID in a terminal:
    - `M303 E0 S220 C8`
    - Retrieve the values `Kp`, `Ki` and `Kd` then:
    - `M301 P`**Kp** `I`**Ki** `D`**Kd**
    - Then `M500` to save.
- Launch a Bed PID in a terminal:
    - `M303 E-1 S90 C8`
    - Retrieve the values `Kp`, `Ki` and `Kd` then:
    - `M304 P`**Kp** `I`**Ki** `D`**Kd**
    - Then `M500` to save.
- Launch an extruder calibration in a terminal:
    - Heat your hotend to its usual operating temperature :
    - `M109 S`**xxx** where `xxx` is temperature
    - Make a pencil mark at 120mm on the filament from the hole on the top of the printer (where we insert the filament)
    - `M83` to switch to relative mode.
    - `G1 E100 F100` for extruding 100mm.
    - Wait until the end of the extrusion and measure if there is still 20mm of the line on the filament until the filament inlet otherwise apply this calculation:
        - To obtain extrusion length: `120 - (value measured between the line and the filament inlet)`
        - To obtain number of steps to have extruded 100mm: `(value of E-steps/mm) x 100`. Default E-Steps value is 415.
        - To obtain the new E-steps/mm: `(number of steps to have extruded 100mm) / (extrusion length)`
    - `M92 E`**(new E-steps/mm)**
    - Then `M500` to save.
- Launch a Delta Calibration a wait until end of process :
    - **Make sure to connect bed level probe before to start the following command**.
    - `G33`
    - Then `M500` to save.
- Start auto-leveling from the TFT screen menu and adjust Z-Offset. Don't forget to save.

Link for a terminal: [Printrun (ex Pronterface)](https://github.com/kliment/Printrun/releases)

## Possible changes :

If you need to make any changes in sources files, please read this for compilation: [here](https://github.com/Guilouz/Marlin-SuperRacer-MKS-Nano-V3/tree/main/_README)

Use VSCode et PlatformIO for compilation (see [here](https://marlinfw.org/docs/basics/install_platformio_vscode.html)).
