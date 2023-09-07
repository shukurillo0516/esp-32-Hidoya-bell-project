void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  // Initialize the watchdog timer with a timeout of 10 seconds
  esp_task_wdt_init(30, true);

  // Register a task to periodically kick the watchdog
  xTaskCreatePinnedToCore(kickWatchdogTask, "kickWatchdogTask", 1000, NULL, 1, NULL, 0);

  Serial.begin(115200);
  Serial.println("\n[*] Creating AP");

  // Wifi Config
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());
  
  initRTC();

  initServer();

  initStorage();
  setAlarmDataFromStorage();
}