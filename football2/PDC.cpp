#include "Arduino.h"
#include "PDC.h"

PDC::PDC(float kp, float kd, float kc) : _kp{kp}, _kd{kd}, _kc{kc} {}

float PDC::get(float error)
{
  _error = error;
  float _u = _kp * _error + _kd * (_error - _prev_error) + _kc * pow(_error, 3);

  Serial.print(_u);
  Serial.print(" = ");
  Serial.print(_kp);
  Serial.print(" * ");
  Serial.print(_error);
  Serial.print(" + ");
  Serial.print(_kd);
  Serial.print(" * ( ");
  Serial.print(_error);
  Serial.print(" - ");
  Serial.print(_prev_error);
  Serial.print(") + ");
  Serial.print(_kc);
  Serial.print(" * ");
  Serial.println(pow(_error, 3));

  _prev_error = _error;
  return _u;
}

void PDC::debug()
{
  Serial.print("PDC:\t");
  Serial.print("KP:\t");
  Serial.print(_kp);
  Serial.print("KD:\t");
  Serial.print(_kd);
  Serial.print("KC:\t");
  Serial.print(_kc);
  Serial.print("error:\t");
  Serial.print(_error);
  Serial.print("prev_error:\t");
  Serial.println(_prev_error);
  Serial.println("==============================================");
}