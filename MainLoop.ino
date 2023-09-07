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
  
  // To prevent the watchdog timer from resetting the ESP32, periodically kick it
  esp_task_wdt_reset();

  delay(MainLoopDelay);//allow the cpu to switch to other tasks
}

void kickWatchdogTask(void *pvParameters) {
  while (1) {
    // Kick the watchdog every second (adjust as needed)
    vTaskDelay(pdMS_TO_TICKS(1000));
    esp_task_wdt_reset();
  }
}