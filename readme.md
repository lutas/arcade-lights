# About
Solution for driving button LEDs on MAME Arcade cabinet. 

![Arcade cabinet lights for reference](https://storage.googleapis.com/lutas-public/img/iot/mame-arcade/DSC_2403.JPG)

# States
The system looks to support the following modes:

1. Machine boot
2. Main menu controls
3. Per-emulator lights enabled for consoles / controllers that are static
4. (Where possible) Per-game lights enabled (e.g. single button game would have one light lit, complex games might have all 6)
5. Support for coin operation. If no coin inserted, disable start button and flash coin button. If coin inserted, flash start button

# Solution layout
The project is composed of the following:
## nano-light-controller
Arduino Nano based lighting system. Communicates over serial (USB) to the host to turn on/off lights as needed

## host
Host app for Raspberry Pi which is hooked into RetroPie launch script.

## scraper
Scraping tool to build data file detailing the systems and per game button configurations for host.'