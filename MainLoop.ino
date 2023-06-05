void loop() {
  server.handleClient();
  checkRingALarm();

  int command;
  if (Serial.available() > 0) {
      command = Serial.parseInt();
  }
  if (command == 1) {
    digitalWrite(led, HIGH);
    Serial.println(command);
  }
  if (command == 2) {
    digitalWrite(led, LOW);
    Serial.println(command);
  }

  if (command == 3) {
    printCurrentTime();
    Serial.println(command);
  }
  

  delay(MainLoopDelay);//allow the cpu to switch to other tasks
}