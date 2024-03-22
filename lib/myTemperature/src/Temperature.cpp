#include "Temperature.h"


// Конструктор
Temperature::Temperature(Adafruit_MAX31855 *sensorBottom, Adafruit_MAX31855 *sensorTop) {
  error = false;
  tBottom = 0;
  tTop = 0;
  this->sensorBottom = sensorBottom;
  this->sensorTop = sensorTop;
}

// Выводит данные для диагностики в Serial
void Temperature::printError(Adafruit_MAX31855 *sensor) {
  error = true;
  uint8_t err = sensor->readError();
  
  if (err & MAX31855_FAULT_OPEN) 
    Serial.println("printError: FAULT: Thermocouple is open - no connections.");
  if (err & MAX31855_FAULT_SHORT_GND) 
    Serial.println("printError: FAULT: Thermocouple is short-circuited to GND.");
  if (err & MAX31855_FAULT_SHORT_VCC) 
    Serial.println("printError: FAULT: Thermocouple is short-circuited to VCC.");
}

// Выводит данные для диагностики в Serial
void Temperature::printTemp(double temperature, Adafruit_MAX31855 *sensor) {
  if (isnan(temperature)) {
    Serial.println("printTemp: Thermocouple fault(s) detected!");
    printError(sensor);
  } else {
    Serial.print("printTemp: C = ");
    Serial.println(temperature);
  }
}

// Обновляет данные о температуре
void Temperature::updateTemp() {
  error = false;
  tBottom = sensorBottom->readCelsius();
  tTop = sensorTop->readCelsius();

  Serial.println("getTemp: Thrtmocouple 1");
  printTemp(tBottom, sensorBottom);
  Serial.println("getTemp: Thrtmocouple 2");
  printTemp(tTop, sensorTop);
}

// Запускается только один раз - инициализация датчиков.
void Temperature::init() {
  Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
  Serial.print("Initializing sensor...");
  if (
    !sensorBottom->begin() &&
    !sensorTop->begin()
  ) {
    Serial.println("ERROR.");
    while (1) delay(10);
  }
  Serial.println("DONE.");
}