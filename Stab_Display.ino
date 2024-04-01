#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Arduino.h>
#include "Blitz.h"
#include "Kreuz.h"

#define TFT_CS 4      // CS Pin; Display CS
#define TFT_RST 5     // Reset Pin; Display RST
#define TFT_DC 3      // DC Pin; Display DC
#define TFT_MOSI 9    // Data out; Display DIN
#define TFT_SCLK 10   // Clock out; Display CLK
#define SIGNAL_PIN_1 1 // Eingang für Signal 1
#define SIGNAL_PIN_2 2 // Eingang für Signal 2

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, HIGH);  // Deaktiviere das Display vor der Initialisierung

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);

  pinMode(SIGNAL_PIN_1, INPUT_PULLUP); // Eingang 1 als Eingang mit Pull-up-Widerstand konfigurieren
  pinMode(SIGNAL_PIN_2, INPUT_PULLUP); // Eingang 2 als Eingang mit Pull-up-Widerstand konfigurieren
}

void loop() {
  if (digitalRead(SIGNAL_PIN_1) == LOW) {
    displayBlitz(); // Wenn Signal an Eingang 1, zeige Blitz an
  } else if (digitalRead(SIGNAL_PIN_2) == LOW) {
    displayKreuz(); // Wenn Signal an Eingang 2, zeige Kreuz an
  } else {
    displayBlack(); // Wenn keine Signale anliegen, zeige schwarzen Bildschirm an
  }
}

void displayBlitz() {
  extern const uint8_t BLITZ[] PROGMEM; // Blitz-Array aus der externen Datei "Blitz.h"
  
  const int8_t BMP_HEIGHT = 160; // Höhe des Bildes
  const int8_t BMP_WIDTH = 80;   // Breite des Bildes

  for (int8_t y = 0; y < BMP_HEIGHT; y++) {
    for (int8_t x = 0; x < BMP_WIDTH; x++) {
      tft.setCursor(x, y); // Setze den Cursor auf die Position (x, y)
      tft.pushColor(pgm_read_byte(&BLITZ[y * BMP_WIDTH + x])); // Setze die Farbe entsprechend des Blitz-Arrays
    }
  }
}

void displayKreuz() {
  extern const uint8_t KREUZ[] PROGMEM; // Kreuz-Array aus der externen Datei "Kreuz.h"
  
  const int8_t BMP_HEIGHT = 160; // Höhe des Bildes
  const int8_t BMP_WIDTH = 80;   // Breite des Bildes

  for (int8_t y = 0; y < BMP_HEIGHT; y++) {
    for (int8_t x = 0; x < BMP_WIDTH; x++) {
      tft.setCursor(x, y); // Setze den Cursor auf die Position (x, y)
      tft.pushColor(pgm_read_byte(&KREUZ[y * BMP_WIDTH + x])); // Setze die Farbe entsprechend des Kreuz-Arrays
    }
  }
}

void displayBlack() {
  tft.fillScreen(ST7735_BLACK); // Display mit schwarzer Farbe füllen
}
