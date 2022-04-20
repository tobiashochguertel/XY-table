#include <Arduino.h>

// Funduino Joystick shield
// www.fambach.net
// GPL2
// ******************************

const byte button[] = {2, 3, 4, 5, 6, 7, 8};
boolean pressed[] = {false, false, false, false, false, false, false};
const int BUTTON_COUNT = 7;
const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;
int analog_x = 350;
int analog_y = 350;

const int MIN_DELTA = 4;
const String TELEGRAM = "[%s;%i;]";

void sendTelegram(String name, int value)
{

  String telegram;
  telegram.reserve(20);
  telegram.concat("#");
  telegram.concat(name);
  telegram.concat(";");
  telegram.concat(value);
  Serial.println(telegram);
}

void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    pinMode(button[i], INPUT);
  }
}

void loop()
{

  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    boolean b = digitalRead(button[i]);
    if (b != pressed[i])
    {
      pressed[i] = b;
      sendTelegram("b" + String(i), (b ? 1 : 0));
    }
  }

  int cur = analogRead(PIN_ANALOG_X);
  int delta = analog_x - cur;

  if (delta > MIN_DELTA || delta < -MIN_DELTA)
  {
    analog_x = cur;
    sendTelegram("ax", cur);
  }

  cur = analogRead(PIN_ANALOG_Y);
  delta = analog_y - cur;

  if (delta > MIN_DELTA || delta < -MIN_DELTA)
  {
    analog_y = cur;
    sendTelegram("ay", cur);
  }
  // delay(100);
}