#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>


#define BOMB_OUT 25
#define LED_COUNT 26
#define UP_BTN 13
#define DOWN_BTN 32
#define ARM_BTN 33

TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library

void displayInit() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(0, 0);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(4);
}


void setup() {
  displayInit();


}
bool ComparacionCodigo(char *ClaveRecibida, char *ClaveCorrecta) {
  int ok = 0;

  for (int i = 0; i < 7; i++) {
    if (ClaveRecibida[i] == ClaveCorrecta[i]) {
      ok++;
    }
  }
  if (ok == 7) {
    return true;
  }
  else {
    return false;
  }

}


void loop() {

  static uint8_t counter = 0;
  static uint32_t reference = 0;

  if ( (millis() - reference) >= 1000) {
    reference = millis();

    tft.fillScreen(TFT_BLACK);
    tft.drawString(String(counter), tft.width() / 2, tft.height() / 2);
    counter++;
  }


}
