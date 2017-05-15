#include <Microduino_Key.h>
#include "colorLed.h"
#include "userDef.h"
#include "eeprom.h"
#include "BasketballJson.h"
#include "game.h"

void setup() {
  Serial.begin(57600);
  strip.begin();
  strip.setBrightness(BRIGHT_MAX);
  read_eeprom();
  if (winThreshold < 1 || winThreshold > 10 || leftColor < 1 || leftColor > 9 || rightColor < 1 || rightColor > 9)
  {
    winThreshold = 5;
    leftColor = 1;
    rightColor = 4;
  }
#if DEBUG
  Serial.println("**************START************");
  Serial.println("--------------");
  Serial.print("RESET DATA:");
  Serial.println(restart);
  Serial.print("WINT DATA:");
  Serial.println(winThreshold);
  Serial.print("LEFTC DATA:");
  Serial.println(leftColor);
  Serial.print("RIGHTC DATA:");
  Serial.println(rightColor);
  Serial.println("--------------");
#endif
  soundInit();
}

void loop() {
  //  Serial.print("LINEA Val:");
  //  Serial.print(analogRead(PIN_LINEA));  //灰度传感器 A 值
  //  Serial.print("\tLINEB Val:");
  //  Serial.println(analogRead(PIN_LINEB));//灰度传感器 B 值
  Basketballjson_data();
  gameReset();
  if (scoreCmp < winThreshold)
    updateScore();
  else
    gameOver();
  delay(15);
}

