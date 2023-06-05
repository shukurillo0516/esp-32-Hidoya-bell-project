void saveData() {
  Serial.println("saveData saveData saveData");

  preferences.begin(alarmStorageName, false);

  int index = 0;
  int len = NULL;
  for (short i = 0; i < server.args(); i += 3) {
    len = server.arg(i+2).toInt();
    // If len exists and values are changed.
    if(len && (alarmsList[index].hour != server.arg(i).toInt() || alarmsList[index].minute != server.arg(i+1).toInt() || alarmsList[index].len != len)) {
      Serial.println("Update Update Update");
      alarmsList[index].hour = server.arg(i).toInt();
      alarmsList[index].minute = server.arg(i+1).toInt();
      alarmsList[index].len = len;

      // Save to flash mem
      preferences.putInt(server.argName(i).c_str(), server.arg(i).toInt());
      preferences.putInt(server.argName(i+1).c_str(), server.arg(i+1).toInt());
      preferences.putInt(server.argName(i+2).c_str(), server.arg(i+2).toInt());
    } else if (len == 0 && alarmsList[index].len != 0) {
     // If alarm deleted
      Serial.println("Delete Delete Delete");
      alarmsList[index].hour = 0;
      alarmsList[index].minute = 0;
      alarmsList[index].len = len;

      // Delete from flash mem
      preferences.remove(server.argName(i).c_str());
      preferences.remove(server.argName(i+1).c_str());
      preferences.remove(server.argName(i+2).c_str());
    }   
    index += 1;
  }

  preferences.end();
}

void setAlarmDataFromStorage() {
  preferences.begin(alarmStorageName, true);
  
  String hourName, minName, lenName;
  int len = 0;
  for (short i = 0; i <= ALarmActualLen; i++ ) {
    hourName = String(i + 1) + "_al_hour";
    minName =  String(i + 1) + "_al_min";
    lenName = String(i + 1) + "_len";

    len = preferences.getInt(lenName.c_str(), 0);
    if(len) {
      alarmsList[i].hour = preferences.getInt(hourName.c_str(), 0);
      alarmsList[i].minute = preferences.getInt(minName.c_str(), 0);
      alarmsList[i].len = len;
    }
  }

  preferences.end();
}

void printAlarmList() {
  Serial.println("Alarm list Alarm list Alarm list");
  for(short i = 0; i < ALarmActualLen; i++) {
    Serial.print(alarmsList[i].hour);
    Serial.print(" ");
    Serial.print(alarmsList[i].minute);
    Serial.print(" ");
    Serial.print(alarmsList[i].len);
    Serial.print(" ");
    Serial.println(i);
  }
}

void initStorage() {
  preferences.begin(alarmStorageName, false);
  preferences.end();
}

