#include "HTInfraredSeeker.h"

class IR
{
public:
  IR(int pin = A14);
  void init();
  void read();
  float angle();
  float strength(); //если больше 180, мяч у нас
  void debug();
private:
  InfraredSeeker _IR;
  int _pin;
  float _angle;
  float _strength;  
};