#ifndef TEMPERATURE_TONAKIHAN

#define TEMPERATURE_TONAKIHAN
#ifndef ADAFRUIT_MAX31855_H
  #include "Adafruit_MAX31855.h"
#endif


class Temperature {
private:
  Adafruit_MAX31855 *sensorBottom;
  Adafruit_MAX31855 *sensorTop;
  
  void printError(Adafruit_MAX31855 *sensor);
  void printTemp(double temperature, Adafruit_MAX31855 *sensor);

public:
  double tBottom;
  double tTop;
  bool error;

  Temperature(Adafruit_MAX31855 *sensorBottom, Adafruit_MAX31855 *sensorTop);
  void updateTemp();
  void init();
};

#endif