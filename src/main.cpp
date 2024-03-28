/** TODO:
 * Настроить коэфициеты PID
 * Настроить кнопки - настройку температуры
 * Меню LCD и кнопок
 * 
 * По клику открывать меню настройки температуры. 
 * Менять информацию 5с/3с currentTemp/targetTemp
 * По прошествии определенного времени тушить дисплей
*/

#include <Adafruit_MAX31855.h>
#include <GyverPID.h>
#include <Tonakihan_Temperature.h>
#include <Tonakihan_LcdMenu.h>
#include <LiquidCrystal_I2C.h>
#include <EncButton.h>

#include "./conf.h"
#include "./initGlobalVariable.h"

// Declaration function
void maskTargetTemp();
void initPages();
void displayMenu();
void displayTemp(double tempTop, double tempBottom);


void setup() {
  temperature.init();
  lcd.init();
  initPages();

  lcd.backlight();

  pinMode(PIN_heating_bottom, OUTPUT);
  pinMode(PIN_heating_top, OUTPUT);

  // Избавляюсь от ложного нажатия (Баг в EncButton v3.5.6)
  for (int i = 0; i < 2; i++) {
    btnMenu.tick(); btnDown.tick(); btnUp.tick();
    btnMenu.press();btnDown.press(); btnUp.press();
    delay(500);
  }
}


void loop() {
  btnMenu.tick(); btnDown.tick(); btnUp.tick();
  
  temperature.updateTemp();
  if (temperature.error) { // При ошибке скидываемся.
    delay(100);
    return;
  };

  if (
    btnMenu.press() || 
    btnDown.press() || 
    btnUp.press()
  ) {
    displayMenu();
  }
  if (millis() - timeLastUpdateTemp > INTERVAL_UPDATE_TEMP) {
    displayTemp(temperature.tTop, temperature.tBottom);
    timeLastUpdateTemp = millis();
  }

  // -- PID --
  // Вход данных
  pidHandlerBottom.input = temperature.tBottom;
  pidHandlerTop.input = temperature.tTop;
  // Цель к чему стремиться
  pidHandlerBottom.setpoint = targetTemp.tBottom;
  pidHandlerTop.setpoint = targetTemp.tTop;
  // Указания от PID
  digitalWrite(PIN_heating_bottom, pidHandlerBottom.getResultTimer());
  digitalWrite(PIN_heating_top, pidHandlerTop.getResultTimer());
}



//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/* -- displayFunc Что то на подобии самостоятельной страницы -- */
// Отображает температуру (любую)
void displayTemp(double tempTop, double tempBottom) {
  if (crrDisplay != "temp") {
    crrDisplay = "temp";
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("tTop :");

    lcd.setCursor(0, 1);
    lcd.print("tBtm :");
  }
  lcd.setCursor(6, 0);
  lcd.print(tempTop);
  lcd.setCursor(6, 1);
  lcd.print(tempBottom);
}

// Выведет температуру-цель
void displaySetTemp(uint16_t &changeTemp) {
  maskTargetTemp();

  while(true) {
    btnMenu.tick(); btnDown.tick(); btnUp.tick();
    if (btnMenu.press()) {
      return;
    }
    if (btnDown.press()) {
      changeTemp-=10;
      maskTargetTemp();
    }
    if (btnUp.press()) {
      changeTemp+=10;
      maskTargetTemp();
    }
  }
}

// Выведет меню 
void displayMenu() {
  crrDisplay = "menu";
  bool exit = false;

  Menu menu(lcd, num_of_pages, &setTempTopPage, &setTempBottomPage);
  menu.launch();
  
  while(!exit) {
    btnMenu.tick(); btnDown.tick(); btnUp.tick();
    if (btnMenu.press()) {
      menu.enter(); 
      crrDisplay = "menu";
      //Временное решение - закрываю меню
      lcd.clear();
      return;
    }
    if (btnDown.press()) {
      menu.down();
    }
    if (btnUp.press()) {
      menu.up();
    }
  }
}

/* -- Надстройки над displayFunc -- */
// Выведет через displayTemp температуру-цель
void maskTargetTemp() {
  displayTemp(static_cast<double>(targetTemp.tTop), static_cast<double>(targetTemp.tBottom));
};

/* Выполняет функцию прослойки между Page и переменными */
//
void maskSetTempTop() {
  displaySetTemp(targetTemp.tTop);
}
void maskSetTempBottom() {
  displaySetTemp(targetTemp.tBottom);
}

void initPages() {
  setTempBottomPage.name = "Set temp bottom";
  setTempBottomPage.callback = &maskSetTempBottom;
  setTempTopPage.name = "Set temp top";
  setTempTopPage.callback = &maskSetTempTop;
}
