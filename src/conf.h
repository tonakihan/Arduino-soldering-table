#pragma once

#define PIN_CS_term_bottom 2
#define PIN_CS_term_top 3
#define PIN_heating_bottom 7
#define PIN_heating_top 8 
#define PIN_button_menu 6
#define PIN_button_down 5
#define PIN_button_up 4
//
#define LCD_COLS 16
#define LCD_ROWS 2 
#define LCD_ADDRESS 0x27
//
#define INTERVAL_UPDATE_TEMP 1000

/* -- EncButton -- */
// отключить поддержку pressFor/holdFor/stepFor и счётчик степов (экономит 2 байта оперативки)
#define EB_NO_FOR
// отключить обработчик событий attach (экономит 2 байта оперативки)
#define EB_NO_CALLBACK
// отключить счётчик энкодера [VirtEncoder, Encoder, EncButton] (экономит 4 байта оперативки)
#define EB_NO_COUNTER
// отключить буферизацию энкодера (экономит 2 байта оперативки)
#define EB_NO_BUFFER
//
/*
  Настройка таймаутов для всех классов
  - Заменяет таймауты константами, изменить их из программы (SetXxxTimeout()) будет нельзя
  - Настройка влияет на все объявленные в программе кнопки/энкодеры
  - Экономит 1 байт оперативки на объект за каждый таймаут
  - Показаны значения по умолчанию в мс
  - Значения не ограничены 4000мс, как при установке из программы (SetXxxTimeout())
*/
#define EB_DEB_TIME 100      // таймаут гашения дребезга кнопки (кнопка)
//#define EB_CLICK_TIME 100   // таймаут ожидания кликов (кнопка)
//#define EB_HOLD_TIME 300    // таймаут удержания (кнопка)
//#define EB_STEP_TIME 300    // таймаут импульсного удержания (кнопка)
//#define EB_FAST_TIME 30     // таймаут быстрого поворота (энкодер)