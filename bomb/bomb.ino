#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>


/*#define BOMB_OUT 25
  #define LED_COUNT 26
  #define UP_BTN 13
  #define DOWN_BTN 32
  #define ARM_BTN 33
*/
#define LED_PIN1 25
#define LED_PIN2 26
#define LED_PIN3 27
#define PUSHBUTTON_PIN1 32
#define PUSHBUTTON_PIN2 33
#define PUSHBUTTON_PIN3 13

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
//funcion que permite comprar la clave intoducida
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
void task1() {
  static char ClaveCorrecta[7] = {'u', 'u', 'd', 'd', 'u', 'd', 'a'};
  static char ClaveIntroducida[7];
  static int DigitosIngresados = 0;
  static int estado = 1;
  static int tiempo = 20;

  static uint32_t previousMillis = 0;
  unsigned long currentMillis = millis();
  const uint32_t interval = 1000;


  switch (estado) {

    case 1: {

        if (digitalRead(13) == LOW) {

          //int dataRX = Serial.read();

          if (tiempo < 60) {
            tiempo++;
            Serial.println(tiempo);

          }
          if (digitalRead(33) == LOW) {

            //int dataRX = Serial.read();

            if (tiempo > 60) {
              tiempo--;
              Serial.println(tiempo);

            }

            else if (digitalRead(32)) {
              estado = 2;
              previousMillis = millis();
              DigitosIngresados = 0;
            }


          }

          break;

        }
      }


    case 2: {
        if (Serial.available() > 0) {
          ClaveIntroducida[DigitosIngresados] = Serial.read();
          DigitosIngresados++;
          Serial.println("digito ingresado");

          if (DigitosIngresados == 7) {

            Serial.println("revisando clave");
            if (ComparacionCodigo(ClaveCorrecta, ClaveIntroducida)) {
              Serial.println("bomba desactivada");
              estado = 1;
              tiempo = 20;
            }
            DigitosIngresados = 0;
          }



        }
        if ((millis() - previousMillis) >= interval) {
          previousMillis = millis();

          if (tiempo > 0) {
            tiempo--;
            Serial.println(tiempo);


          }
          else {
            Serial.println("la bomba exploto");

            estado = 1;
            tiempo = 20;
          }


        }
        break;
      }
    default:
      Serial.println("ERROR");

      break;


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
