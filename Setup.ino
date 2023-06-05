void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);


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