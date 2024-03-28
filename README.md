# Arduino soldering table

Это паяльный стол на arduino.

## Использование
1. Настроить коэфициенты PID  

initGlobalVariable.h
```cpp
  pidHandlerBottom(0.1, 0.1, 0.1, 500), // Подобрать параметры PID
  pidHandlerTop(0.1, 0.1, 0.1, 500); // Подобрать параметры PID
```
2. Настроит конфигурацию своего устройства
conf.h
```cpp
#define PIN_CS_term_bottom 2
#define PIN_CS_term_top 3
#define PIN_heating_bottom 7
#define PIN_heating_top 8 
#define PIN_button_menu 6
#define PIN_button_down 5
#define PIN_button_up 4

#define LCD_COLS 16
#define LCD_ROWS 2 
#define LCD_ADDRESS 0x27
```