void initRTC() {
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
}


void printCurrentTime() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.println();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

void checkRingALarm() {
  DateTime now = rtc.now();
  DateTime alarm; 
  for(short i = 0; i < ALarmActualLen; i++) {
    if (alarmsList[i].len != 0) {
      alarm = DateTime(now.year(), now.month(), now.day(), alarmsList[i].hour, alarmsList[i].minute, 0);
      now = rtc.now();
      while (now.unixtime() >= alarm.unixtime() && now.unixtime() < (alarm.unixtime() + alarmsList[i].len)) {
        now = rtc.now();
        digitalWrite(led, LOW);
        delay(500);
      }
      digitalWrite(led, HIGH);
    }
  }
}
