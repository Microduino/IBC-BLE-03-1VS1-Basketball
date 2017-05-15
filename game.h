Key keyLineA(PIN_LINEA, INPUT_PULLUP);
Key keyLineB(PIN_LINEB, INPUT_PULLUP);
Key keyButton(PIN_KEY, INPUT_PULLUP);

uint8_t scoreA, scoreB, scoreCmp;
uint8_t colorNum;
uint32_t scoreTimer;

//----------ColorLED和Buzzer--------------//
void soundInit()
{
  setAllLed(COLOR_RED);
  tone(PIN_BUZZER, 1000);
  delay(500);
  setAllLed(COLOR_NONE);
  noTone(PIN_BUZZER);
  delay(500);
  setAllLed(COLOR_WARM);
  tone(PIN_BUZZER, 1000);
  delay(500);
  setAllLed(COLOR_NONE);
  noTone(PIN_BUZZER);
  delay(500);
  setAllLed(COLOR_GREEN);
  tone(PIN_BUZZER, 1500);
  delay(500);
  noTone(PIN_BUZZER);
  setAllLed(COLOR_NONE);
}

//------------得分-------------//
void updateScore()
{
  if (keyLineA.read(0, DOCK_MAX) == SHORT_PRESS)
  {
    tone(PIN_BUZZER, 600, 300);
    setAllLed(COLOR_NONE);
    ledBlinkNum(1, leftColor, 0, 5);
    if (scoreA < 255)
      scoreA++;
    else
      scoreA = 255;
    scoreupload(0, scoreA);
    scoreCmp = abs(scoreA - scoreB);
  }
  else if (keyLineB.read(0, DOCK_MAX) == SHORT_PRESS)
  {
    tone(PIN_BUZZER, 600, 300);
    setAllLed(COLOR_NONE);
    ledBlinkNum(1, rightColor, 1, 5);
    if (scoreB < 255)
      scoreB++;
    else
      scoreB = 255;
    scoreupload(1, scoreB);
    scoreCmp = abs(scoreA - scoreB);
  }
}

void gameReset()
{
  if (keyButton.read() == LONG_PRESS || restart == "true")
  {
    restart = "";
    if (scoreA != 0 || scoreB != 0)
    {
      scoreA = 0;
      scoreB = 0;
      scoreCmp = 0;
      setAllLed(COLOR_NONE);
      write_eeprom();
      scoreupload(0, scoreA);
      delay(30);
      scoreupload(1, scoreB);
      delay(30);
    }
    soundInit();
  }
}

//------------游戏结束-------------//
void gameOver()
{
  uint32_t bTimer = millis();
  while (millis() - bTimer < 300)
  {
    if (colorNum % 2)
    {
      if (scoreA > scoreB)
        setAllLed(leftColor);
      else
        setAllLed(rightColor);
      tone(PIN_BUZZER, 1000);
    }
    else
    {
      noTone(PIN_BUZZER);
      setAllLed(COLOR_NONE);
    }
    gameReset();
  }
  colorNum++;
  if (colorNum > 9)
    colorNum = 1;
}
