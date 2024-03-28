#pragma once

#include <GyverPID.h>
#include <Tonakihan_Temperature.h>
#include <Tonakihan_LcdMenu.h>
#include <LiquidCrystal_I2C.h>
#include <EncButton.h>
#include "./conf.h"

// Кнопки
Button 
  btnMenu(PIN_button_menu, INPUT),
  btnDown(PIN_button_down, INPUT),
  btnUp(PIN_button_up, INPUT);

// Термопары
Temperature temperature(PIN_CS_term_bottom, PIN_CS_term_top);

// PID регуляторы
GyverPID 
  pidHandlerBottom(0.1, 0.1, 0.1, 500), // Подобрать параметры PID
  pidHandlerTop(0.1, 0.1, 0.1, 500); // Подобрать параметры PID

// LCD дисплей
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);
//
// Страницы
#define num_of_pages 2
Page 
  setTempTopPage,
  setTempBottomPage;
//
String crrDisplay;

struct  {
  uint16_t tTop = 0;
  uint16_t tBottom = 0;
} targetTemp;

unsigned long timeLastUpdateTemp = INTERVAL_UPDATE_TEMP;
