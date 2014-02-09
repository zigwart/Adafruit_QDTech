/*
  An example analogue/digital clock using a TFT LCD screen to show the 
  use of some of the drawing commands with the Adafruit_QDTech library.
  For a more accurate clock, it would be better to use the RTClib library.
  But this is just a demo. 

  This examples uses the hardware SPI only. Non-hardware SPI
  is just too slow (~8 times slower!)

  Gilchrist 6/2/2014 1.0
*/

#define sclk 13  // Don't change
#define mosi 11  // Don't change
#define cs   9
#define dc   8
#define rst  7  // you can also connect this to the Arduino reset
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_QDTech.h> // Hardware-specific library
#include <SPI.h>

Adafruit_QDTech tft = Adafruit_QDTech(cs, dc, rst);       // Invoke custom library

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=64, osy=64, omx=64, omy=64, ohx=64, ohy=64;  // Saved H, M, S x & y coords
uint16_t x0=0, x1=0, y0=0, y1=0;
uint32_t targetTime = 0;                    // for next 1 second timeout
uint8_t hh=conv2d(__TIME__), mm=conv2d(__TIME__+3), ss=conv2d(__TIME__+6);  // Get H, M, S from compile time

void setup(void) {
  tft.init();

  tft.setRotation(0);
  tft.fillScreen(QDTech_BLACK);
  tft.setTextColor(QDTech_WHITE, QDTech_BLACK);  // Adding a black background colour erases previous text automatically
  
  // Draw clock face
  tft.fillCircle(64, 64, 61, QDTech_BLUE);
  tft.fillCircle(64, 64, 57, QDTech_BLACK);

  // Draw 12 lines
  for(int i = 0; i<360; i+= 30) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x0 = sx*57+64;
    y0 = sy*57+64;
    x1 = sx*50+64;
    y1 = sy*50+64;
    
    tft.drawLine(x0, y0, x1, y1, QDTech_BLUE);
  }
  tft.fillCircle(65, 65, 3, QDTech_RED);
  tft.setCursor (34, 151);
  tft.print(__DATE__);
  targetTime = millis() + 1000; 
}

void loop() {
  if (targetTime < millis()) {
    targetTime = millis()+1000;
    ss++;              // Advance second
    if (ss==60) {
      ss=0;
      mm++;            // Advance minute
      if(mm>59) {
        mm=0;
        hh++;          // Advance hour
        if (hh>23) {
          hh=0;
        }
      }
    }

    // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = ss*6;                  // 0-59 -> 0-354
    mdeg = mm*6+sdeg*0.01666667;  // 0-59 -> 0-360 - includes seconds
    hdeg = hh*30+mdeg*0.0833333;  // 0-11 -> 0-360 - includes minutes and seconds
    hx = cos((hdeg-90)*0.0174532925);    hy = sin((hdeg-90)*0.0174532925);
    mx = cos((mdeg-90)*0.0174532925);    my = sin((mdeg-90)*0.0174532925);
    sx = cos((sdeg-90)*0.0174532925);    sy = sin((sdeg-90)*0.0174532925);

    // Erase just old hand positions
    tft.drawLine(ohx, ohy, 65, 65, QDTech_BLACK);  
    tft.drawLine(omx, omy, 65, 65, QDTech_BLACK);  
    tft.drawLine(osx, osy, 65, 65, QDTech_BLACK);
    // Draw new hand positions  
    tft.drawLine(hx*33+65, hy*33+65, 65, 65, QDTech_WHITE);
    tft.drawLine(mx*44+65, my*44+65, 65, 65, QDTech_WHITE);
    tft.drawLine(sx*47+65, sy*47+65, 65, 65, QDTech_RED);
    tft.fillCircle(65, 65, 3, QDTech_RED);

    // Update old x&y coords
    osx = sx*47+65;    osy = sy*47+65;
    omx = mx*44+65;    omy = my*44+65;
    ohx = hx*33+65;    ohy = hy*33+65;

    // Update digital time
    tft.setCursor (34, 140);

    if(hh>12) {
      if (hh<22) tft.print('0');      
      tft.print (hh-12);
    } else {
      if (hh<10) tft.print('0');
      tft.print (hh);
    }
    tft.print (':');
    if (mm<10) tft.print('0');
    tft.print (mm);
    tft.print (':');
    if (ss<10) tft.print('0');
    tft.print (ss);
    if (hh>12) tft.print(" pm"); else tft.print (" am");
  }
}

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
