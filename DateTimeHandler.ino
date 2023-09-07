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

String getCurrentTime() {
    DateTime now = rtc.now();
    String formattedTime = String(now.year()) + "-" +
                          String(now.month()) + "-" +
                          String(now.day()) + " " +
                          String(now.hour()) + ":" +
                          String(now.minute()) + ":" +
                          String(now.second());
    return formattedTime;
}

void printCurrentTime() {
  Serial.println(getCurrentTime());
}

int getCurrentSeconds() {
  DateTime now = rtc.now();
  return now.second() + now.minute() * 60 + now.hour() * 3600;
}

void checkRingALarm() {
  int nowSecs = getCurrentSeconds();
  int alarmSecs = 0;
  for(short i = 0; i < ALarmActualLen; i++) {
    if (alarmsList[i].len != 0) {    
      alarmSecs = alarmsList[i].hour * 3600 + alarmsList[i].minute * 60;
      if (nowSecs >= alarmSecs && nowSecs < (alarmSecs + alarmsList[i].len)) {
        digitalWrite(led, LOW);
        delay(alarmsList[i].len * 1000 + 100);
        nowSecs = getCurrentSeconds();
        digitalWrite(led, HIGH);
      }
    }
  }
}
