/***************************************************
	This is a modification of the Adafruit SPI LCD library,
	customised for hardware SPI and the QDTech board 
	using a Samsung S6D02A1 chip.

	Most changes are made to the initialisation routine but
	non-Arduino code has been removed too.

	The initialisation sequence comes from Henning Karlsen's
	UTFT library: http://henningkarlsen.com

	Using the hardware SPI pins is highly recommeneded.
	
	You will also need the stock "Adafruit_GFX" library.
	https://github.com/adafruit/Adafruit-GFX-Library

	Gilchrist 30/1/2014
	6/2/14	1.1	Fixed RGB colour order error

/***************************************************
  This is a library for the Adafruit 1.8" SPI display.
  This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
  as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef Adafruit_QDTech_h
#define Adafruit_QDTech_h

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif

#include <Adafruit_GFX.h>
#include <avr/pgmspace.h>

#define QDTech_TFTWIDTH  128
#define QDTech_TFTHEIGHT 160

// Some used command definitions kept from original
#define QDTech_INVOFF  0x20
#define QDTech_INVON   0x21
#define QDTech_DISPOFF 0x28
#define QDTech_DISPON  0x29
#define QDTech_CASET   0x2A
#define QDTech_RASET   0x2B
#define QDTech_RAMWR   0x2C
#define QDTech_RAMRD   0x2E

#define QDTech_PTLAR   0x30
#define QDTech_COLMOD  0x3A
#define QDTech_MADCTL  0x36

// Basic colour definitions
#define	QDTech_BLACK   0x0000
#define	QDTech_RED     0xF800
#define	QDTech_GREEN   0x07E0
#define	QDTech_BLUE    0x001F
#define QDTech_YELLOW  0xFFE0
#define QDTech_MAGENTA 0xF81F
#define QDTech_CYAN    0x07FF  
#define QDTech_WHITE   0xFFFF
#define QDTech_GREY    0x632C


class Adafruit_QDTech : public Adafruit_GFX {

 public:

  Adafruit_QDTech(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK, uint8_t RST);
  Adafruit_QDTech(uint8_t CS, uint8_t RS, uint8_t RST);

  void     init(),
           setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1),
           pushColor(uint16_t color),
           fillScreen(uint16_t color),
           drawPixel(int16_t x, int16_t y, uint16_t color),
           drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
           drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
           fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
           setRotation(uint8_t r),
           invertDisplay(boolean i);

uint16_t	Color565(uint8_t r, uint8_t g, uint8_t b);

 private:
  uint8_t  tabcolor;

  void     spiwrite(uint8_t),
           writecommand(uint8_t c),
           writedata(uint8_t d),
           commandList(const uint8_t *addr),
           commonInit(const uint8_t *cmdList);
           
  boolean  hwSPI;

volatile uint8_t *dataport, *clkport, *csport, *rsport;
  uint8_t  _cs, _rs, _rst, _sid, _sclk,
           datapinmask, clkpinmask, cspinmask, rspinmask,
           colstart, rowstart; // some displays need this changed

};
#endif
