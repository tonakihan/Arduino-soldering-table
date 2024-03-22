#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "Temperature.h"

#define CS_term_pin_bottom 2
#define CS_term_pin_top 3

Adafruit_MAX31855 thermocoupleBottom(CS_term_pin_bottom);
Adafruit_MAX31855 thermocoupleTop(CS_term_pin_top);

Temperature objTemp(
  &thermocoupleBottom,
  &thermocoupleTop
);

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  objTemp.init();
}

void loop() {
  objTemp.updateTemp();
  if (objTemp.error) { // При ошибке скидываемся.
    delay(300);
    return;
  };

  // Использование данных:
  Serial.println(objTemp.tBottom);
  Serial.println(objTemp.tTop);

  delay(1000);
}
