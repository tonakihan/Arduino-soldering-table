#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "GyverPID.h"
#include <Temperature.h>

#define CS_term_pin_bottom 2
#define CS_term_pin_top 3
#define heating_pin_bottom 0 // TODO
#define heating_pin_top 0 // TODO

// ТЕРМОПАРЫ
Adafruit_MAX31855 thermocoupleBottom(CS_term_pin_bottom);
Adafruit_MAX31855 thermocoupleTop(CS_term_pin_top);
//
Temperature objTemp(
  &thermocoupleBottom,
  &thermocoupleTop
);

// PID регуляторы
GyverPID pidHandlerBottom(0, 0, 0, 500); // Подобрать параметры PID
GyverPID pidHandlerTop(0, 0, 0, 500); // Подобрать параметры PID

/** TODO:
 * Настроить коэфициеты PID
 * Подклюdчить LED
 * Настроить кнопки - настройку температуры
*/

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


  pidHandlerBottom.input = objTemp.tBottom;
  pidHandlerTop.input = objTemp.tTop;
  pidHandlerBottom.setpoint = 0;
  pidHandlerTop.setpoint = 0;

  // TODO: Передать в управляющий сигнал
  pidHandlerBottom.getResultTimer();
  pidHandlerTop.getResultTimer();

  delay(1000);
}
