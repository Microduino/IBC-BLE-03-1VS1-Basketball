#include <aJSON.h>
aJsonStream serial_stream(&Serial);

String restart = "";
String winT = "";
String leftC = "";
String ringhC = "";
String projtctid = "";

String ID = "{\"ID\":\"590bc5e87bb3e300016e2d9f\"}";

//{"leftScore":0}
//{"rightScore":1}
aJsonObject *createMessage(uint8_t x, uint8_t y)
{
  aJsonObject *msg = aJson.createObject();
  aJsonObject *analog = aJson.createItem(y);
  if (x == 0)
    aJson.addItemToObject(msg, "leftScore", analog);
  else if (x == 1)
    aJson.addItemToObject(msg, "rightScore", analog);
  return msg;
}

//{"ID":"project"}
void IDupload()
{
  Serial.print(ID.substring(0, 17));
  delay(30);
  Serial.println(ID.substring(17, 33));
  delay(30);
}

void Ctrldata(String _st, int _data)
{
  String send_data;
  int number;
  send_data = "{\"";
  send_data += _st;
  send_data += "\":\"";
  send_data += _data;
  send_data += "\"\}";
  number = send_data.length() / 17;

  if (number == 0)
  {
    Serial.println(send_data);
    delay(30);
  }
  else
  {
    while (number >= 0)
    {
      Serial.print(send_data.substring(0, 17));
      send_data = send_data.substring(17, send_data.length());
      delay(30);
      number--;
    }
    Serial.print("\n");
  }
}

//{"restart":"true"}
//{"winThreshold":"3"}
//{"leftColor":"1"}
//{"rightColor":"5"}

void ComExecution(aJsonObject *msg)
{
  aJsonObject *IDval = aJson.getObjectItem(msg, "ID");
  if (IDval) {
    projtctid = IDval->valuestring;
    if (projtctid == "project")
    {
      IDupload();
      Ctrldata("winThreshold", winThreshold);
      Ctrldata("leftColor", leftColor);
      Ctrldata("rightColor", rightColor);
    }
  }
  else {
#if DEBUG
    Serial.println("no ID data");
#endif
  }

  aJsonObject *resetval = aJson.getObjectItem(msg, "restart");
  if (resetval) {
    restart = resetval->valuestring;
  }
  else {
#if DEBUG
    Serial.println("no rightCval data");
#endif
  }
  aJsonObject *winTval = aJson.getObjectItem(msg, "winThreshold");
  if (winTval) {
    winT = winTval->valuestring;
    winThreshold = winT.toInt();
    ledBlinkNum(1, leftColor, 0, 10);
    ledBlinkNum(1, rightColor, 1, 10);
    write_eeprom();
  }
  else {
#if DEBUG
    Serial.println("no winTval data");
#endif
  }
  aJsonObject *leftCval = aJson.getObjectItem(msg, "leftColor");
  if (leftCval) {
    leftC = leftCval->valuestring;
    leftColor = leftC.toInt();
    ledBlinkNum(1, leftColor, 0, 100);
    write_eeprom();
  }
  else {
#if DEBUG
    Serial.println("no leftCval data");
#endif
  }
  aJsonObject *rightCval = aJson.getObjectItem(msg, "rightColor");
  if (rightCval) {
    ringhC = rightCval->valuestring;
    rightColor = ringhC.toInt();
    ledBlinkNum(1, rightColor, 1, 100);
    write_eeprom();
  }
  else {
#if DEBUG
    Serial.println("no rightCval data");
#endif
  }
#if DEBUG
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
}

void Basketballjson_data()
{
  if (serial_stream.available()) {
    serial_stream.skip();
  }
  if (serial_stream.available()) {
    aJsonObject *msg = aJson.parse(&serial_stream);
    ComExecution(msg);
    aJson.deleteItem(msg);
  }
}

void scoreupload(uint8_t x, uint8_t y)
{
  aJsonObject *msg = createMessage(x, y);
  aJson.print(msg, &serial_stream);
  Serial.println();
  aJson.deleteItem(msg);
}

