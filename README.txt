***************************************************
	This is a modification of the Adafruit SPI TFT LCD Arduino 
	library, customised for hardware SPI and the QDTech 1.8" 
	128x160 pixel LCD board using a Samsung S6D02A1 chip.

	Most changes are made to the initialisation routine but
	non-Arduino code has been removed too.

	The initialisation sequence comes from Henning Karlsen's
	UTFT library: http://henningkarlsen.com

	Using the hardware SPI pins is highly recommeneded.
	
	Unzip and change the folder name to "Adafruit_QDTech".
	Copy the folder into your
	<arduinosketchfolder>/libraries/ folder.
	
	You will also need the stock "Adafruit_GFX" library.
	https://github.com/adafruit/Adafruit-GFX-Library

	Gilchrist 30/1/2014
	6/2/14	1.1	Fixed RGB colour order error

***************************************************

This is a library for the Adafruit 1.8" SPI display.
This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
 
Check out the links above for our tutorials and wiring diagrams.
These displays use SPI to communicate, 4 or 5 pins are required
to interface (RST is optional).
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
MIT license, all text above must be included in any redistribution

To download. click the DOWNLOADS button in the top right corner, 
rename the uncompressed folder Adafruit_ST7735. Check that the 
Adafruit_ST7735 folder contains Adafruit_ST7735.cpp and Adafruit_ST7735.

Place the Adafruit_ST7735 library folder your
<arduinosketchfolder>/libraries/ folder. You may need to create the 
libraries subfolder if its your first library. Restart the IDE

Also requires the Adafruit_GFX library for Arduino.
