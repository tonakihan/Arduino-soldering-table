/* Сделать так:
  По истечении времени от последнего нажатия -> возврат
*/ 
#include "Tonakihan_LcdMenu.h"


// Выводит на дисплей список
void Menu::printList() {
  lcd->clear();
  for ( uint8_t i = 0; i < LCD_MENU_ROWS; i++ ) {
    lcd->setCursor(1, i);
    lcd->print(pages[activeLcdLine+i]->name);
  }
}

// Отображает курсор
void Menu::printCursor() {
  lcd->setCursor(0, activeLcdLine - activePage);
  lcd->print(">");
}

// Принимает lcd, кол-во страниц, страницы
Menu::Menu(LiquidCrystal_I2C &lcd, uint8_t numOfPages, Page *firstPage, ...) {
  this->lcd = &lcd;
  this->numOfPages = numOfPages;

  this->pages = new Page*[numOfPages];
  this->pages[0] = firstPage;

  va_list args;
  va_start(args, firstPage);
  for (int i = 1; i < numOfPages; i++) {
    this->pages[i] = va_arg(args, Page*);
  }
  va_end(args);
}

Menu::~Menu() {
  delete[] pages;
}

void Menu::up() {
  // Если в начале меню
  if (activePage <= 0) {
    return;
  }
  activePage--;

  // Если выбранная страница за пределами экрана
  if (activePage < activeLcdLine) {
    activeLcdLine--;
  }
  launch();
}

void Menu::down() {
  //Если в конце меню
  if (activePage >= numOfPages-1) {
    return;
  }
  activePage++;

  // Если выбранная страница за пределами экрана
  if (activePage > activeLcdLine+LCD_MENU_ROWS-1) {
    activeLcdLine++;
  }
  launch();
}

void Menu::enter() {
  lcd->clear();
  pages[activePage]->callback();
  launch();
}

void Menu::launch() {
  printList();
  printCursor();
}
