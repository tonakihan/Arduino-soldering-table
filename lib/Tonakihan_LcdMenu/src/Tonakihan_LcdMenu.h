/*
  Обязательно настрой confMenu.h перед началом
*/
#pragma once

#include "LiquidCrystal_I2C.h"

//Настройка параметров lcd
#ifdef LCD_ROWS
#define LCD_MENU_COLS LCD_ROWS
#else
#define LCD_MENU_COLS 16
#endif
#ifdef LCD_COLS
#define LCD_MENU_ROWS (LCD_COLS)
#else
#define LCD_MENU_ROWS 2
#endif


struct Page {
  String name;
  void (*callback)();
};

class Menu {
private:
  LiquidCrystal_I2C *lcd;
  uint8_t activePage = 0; // Активная страница, также активная строка для указателя
  uint8_t activeLcdLine = 0; // Отображаемая на дисплее первая строка 
  uint8_t numOfPages; //Количество пунктов меню
  Page **pages;

  // Выводит на дисплей список
  void printList();
  void printCursor();

public:
  Menu (LiquidCrystal_I2C &lcd, uint8_t numOfPages, Page *firstPage, ...);
  ~Menu();

  void up();
  void down();
  void enter();
  void launch();
};
