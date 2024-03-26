/** TODO:
 * Настроить коэфициеты PID
 * Настроить кнопки - настройку температуры
 * Меню LCD и кнопок
 * 
 * По клику открывать меню настройки температуры. 
 * Менять информацию 5с/3с currentTemp/targetTemp
 * По прошествии определенного времени тушить дисплей
*/

#include "Adafruit_MAX31855.h"
#include "GyverPID.h"
#include "Temperature.h"
#include "LiquidCrystal_I2C.h"

#define PIN_CS_term_bottom 2
#define PIN_CS_term_top 3
#define PIN_heating_bottom 7
#define PIN_heating_pin_top 8 
#define PIN_button_menu 6
#define PIN_button_down 5
#define PIN_button_up 4
//
#define LCD_COLS 16
#define LCD_ROWS 2 
#define LCD_ADDRESS 0x27
//
#define TIMEOUT_ONCLICK 150

// ТЕРМОПАРЫ
Temperature temperature(PIN_CS_term_bottom, PIN_CS_term_top);

// PID регуляторы
GyverPID pidHandlerBottom(0.1, 0.1, 0.1, 500); // Подобрать параметры PID
GyverPID pidHandlerTop(0.1, 0.1, 0.1, 500); // Подобрать параметры PID

// LCD дисплей
LiquidCrystal_I2C lcdd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);


struct TargetTemp {
  uint16_t tTop = 0;
  uint16_t tBottom = 0;
};
TargetTemp targetTemp;


class Menu {
private:
  LiquidCrystal_I2C* lcd;

public:
  Menu(uint8_t lcdAddres, uint8_t lcdRows, uint8_t lcdColumn) {
    lcd = new LiquidCrystal_I2C(lcdAddres, lcdColumn, lcdRows);
  }
  Menu(LiquidCrystal_I2C *lcd) {
    this->lcd = lcd;
  } 

  // Ставит 'H' если греет
  void markHeating(uint8_t numLine, GyverPID &pid) {
    if (pid.getResultTimer()) {
      lcd->setCursor(15, numLine);
      lcd->print('H');
    } else {
      lcd->setCursor(15, numLine);
      lcd->print(' ');
    }
  }

  // Выбор позиции и печать
  void setCursor(uint8_t col, uint8_t row) {
    lcd->setCursor(col, row);
  }
  void print(String line) {
    lcd->print(line);
  }
};
Menu menu(&lcdd);


void setup() {
  Serial.begin(9600);
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

  temperature.init();
  lcdd.init();

  lcdd.backlight();

  lcdd.setCursor(0, 0);
  lcdd.print("Top :");
  lcdd.setCursor(0, 1);
  lcdd.print("Btm :");

  pinMode(PIN_button_menu, INPUT);
  pinMode(PIN_button_down, INPUT);
  pinMode(PIN_button_up, INPUT);
  pinMode(PIN_heating_bottom, OUTPUT);
  pinMode(PIN_heating_pin_top, OUTPUT);
}


void loop() {
  Serial.println("DATA : ");
  Serial.println(targetTemp.tTop);

  if (digitalRead(PIN_button_menu)) {
    delay(TIMEOUT_ONCLICK);
  }
  if (digitalRead(PIN_button_up)) {
    targetTemp.tTop += 10;
    delay(TIMEOUT_ONCLICK);
  }
  if (digitalRead(PIN_button_down)) {
    delay(TIMEOUT_ONCLICK);
    targetTemp.tTop -= 10;
  }

  temperature.updateTemp();
  if (temperature.error) { // При ошибке скидываемся.
    delay(300);
    return;
  };

  lcdd.setCursor(8, 0);
  lcdd.print(temperature.tTop);
  lcdd.setCursor(8, 1);
  lcdd.print(temperature.tBottom);

  // -- PID --
  // Вход данных
  pidHandlerBottom.input = temperature.tBottom;
  pidHandlerTop.input = temperature.tTop;
  // Цель к чему стремиться
  pidHandlerBottom.setpoint = targetTemp.tBottom;
  pidHandlerTop.setpoint = targetTemp.tTop;
  // Указания от PID
  digitalWrite(PIN_heating_bottom, pidHandlerBottom.getResultTimer());
  digitalWrite(PIN_heating_pin_top, pidHandlerTop.getResultTimer());

  menu.markHeating(0, pidHandlerTop);
  menu.markHeating(1, pidHandlerBottom);

  //delay(1000); // Заменить
}
