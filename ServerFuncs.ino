void handleRoot() {
  String httpMethod = (server.method() == HTTP_GET) ? "GET" : "POST";
  if (httpMethod == "POST") {
    saveData();
  } 
  String page = getIndexPage();
  server.send(200, "text/html", page);
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void initServer() {
  // MDNS Config
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  // URLS
  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  // Server Start
  server.begin();
  Serial.println("HTTP server started");
}