#ifndef TEMPERATURE_TONAKIHAN

//#define DEBUG //FOR PRINT DATA TO SERIAL
#define TEMPERATURE_TONAKIHAN
#include "Adafruit_MAX31855.h"


class Temperature {
private:
  Adafruit_MAX31855 *sensorBottom;
  Adafruit_MAX31855 *sensorTop;
  
  #ifdef DEBUG
  void printError(Adafruit_MAX31855 *sensor);
  void printTemp(double temperature, Adafruit_MAX31855 *sensor);
  #else
  void checkTemp(double temperature);
  #endif

public:
  double tBottom;
  double tTop;
  bool error;

  Temperature(Adafruit_MAX31855 *sensorBottom, Adafruit_MAX31855 *sensorTop);
  Temperature(uint8_t pinBottom, uint8_t pinTop);
  void updateTemp();
  void init();
};

#endif
