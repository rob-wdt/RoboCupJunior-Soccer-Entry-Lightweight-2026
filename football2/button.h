#include "pins_arduino.h"
class Button
{
public:
  Button(int pin = A3);
  void init();
  void read();
  bool is_pressed();
  void debug();
private:
  int _pin;
  bool _is_pressed{};
};