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

void handleGetTime() {
    String currentTime = getCurrentTime();
    server.send(200, "text/plain", currentTime);
}

void handleSetDateTime() {
    if (server.hasArg("date") && server.hasArg("hours") && server.hasArg("minutes") && server.hasArg("seconds")) {
        String newDate = server.arg("date");
        int newHours = server.arg("hours").toInt();
        int newMinutes = server.arg("minutes").toInt();
        int newSeconds = server.arg("seconds").toInt();

        // Validate the date and time values if needed

        // Create a DateTime object with the new values
        DateTime newDateTime(newDate.substring(0, 4).toInt(), // Year
                             newDate.substring(5, 7).toInt(), // Month
                             newDate.substring(8, 10).toInt(), // Day
                             newHours, newMinutes, newSeconds);

        // Adjust the RTC DS3231 with the new date and time
        rtc.adjust(newDateTime);

        // Optionally, you can redirect the user to a confirmation page
        server.sendHeader("Location", "/", true);
        server.send(302, "text/plain", "Date and Time Set");
    } else {
        // Handle form data missing or incorrect
        server.send(400, "text/plain", "Bad Request");
    }
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
  server.on("/gettime", HTTP_GET, handleGetTime);
  server.on("/setdatetime", HTTP_POST, handleSetDateTime);
  server.onNotFound(handleNotFound);
  // Server Start
  server.begin();
  Serial.println("HTTP server started");
}