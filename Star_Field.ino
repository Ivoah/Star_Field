#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

// These are the pins used for the UNO
// for Due/Mega/Leonardo use the hardware SPI pins (which are different)
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _rst 9
#define _dc 8

// Using software SPI is really not suggested, its incredibly slow
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

/*
int WIDTH;
int HEIGHT;

int CX;
int CY;
*/

#define parts 117

double x[parts];
double y[parts];

double ox[parts];
double oy[parts];

void setup() {
  randomSeed(analogRead(A0));
  tft.begin();
  tft.fillScreen(ILI9340_BLACK);
  
  /*
  WIDTH = tft.width();
  HEIGHT = tft.height();
  
  CX = WIDTH/2;
  CY = HEIGHT/2;
  */
  
  for (int i = 0; i < parts; i++) {
    
    x[i] = random(tft.width());
    y[i] = random(tft.height());
    
    ox[i] = !x[i];
    oy[i] = !y[i];
    
  }
  
}

void loop() {
  
  for (int i = 0; i < parts; i++) {
    
    x[i] += (x[i] - tft.width()/2.0)/analogRead(A0);
    y[i] += (y[i] - tft.height()/2.0)/analogRead(A0);
    
    if (x[i] > tft.width() || x[i] < 0 || y[i] > tft.height() || y[i] < 0 || x[i] == tft.width()/2.0 || y[i] == tft.height()/2.0) {
      x[i] = random(tft.width()/2.0 - 25, tft.width()/2.0 + 26);
      y[i] = random(tft.height()/2.0 - 25, tft.height()/2.0 + 26);
    }
    
    if (ox[i] != x[i] || oy[i] != y[i]) {
      tft.drawPixel(ox[i], oy[i], ILI9340_BLACK);
      ox[i] = x[i];
      oy[i] = y[i];
    }
    
    tft.drawPixel(x[i], y[i], ILI9340_WHITE);
    
  }
  
  //delay(analogRead(A0));
  
}
