String getAlarmSd() {
  String data = "{";
  String hourName, minName, lenName;
  for (short i = 0; i <= ALarmActualLen; i++ ) {
    hourName = String(i + 1) + "_al_hour";
    minName =  String(i + 1) + "_al_min";
    lenName = String(i + 1) + "_len";
    
    data += "\"" + hourName + "\"" + ":" + String(alarmsList[i].hour) + ",";
    data += "\"" + minName + "\""  + ":" + String(alarmsList[i].minute) + ",";
    data += "\"" + lenName + "\"" + ":" + String(alarmsList[i].len)  + ",";
  }
  data += "};\n";
  return data;
}

String getHeader() {
  String page = "<!DOCTYPE html>\n";
  page += "<html lang=\"en\">\n";
  page += "<head>\n";
  page += "<meta charset=\"UTF-8\">\n";
  page += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  page += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  page += "<title>Hidoya</title>\n";
  page += "<style>\n";
  page += "body {\n";
  page += "width: 100%;\n";
  page += "}\n";
  page += ".form-group {\n";
  page += "width: 100%;\n";
  page += "}\n";
  page += "h4 {\n";
  page += "margin: auto 0;\n";
  page += "}\n";
  page += "\n";
  page += ".submit-btn {\n";
  page += "background-color: #48b4ff;\n";
  page += "font-size: 22px;\n";
  page += "}\n";
  page += "@media (min-width: 413px) {\n";
  page += ".main-content {\n";
  page += "text-align: center;\n";
  page += "}\n";
  page += "#alarm-form {\n";
  page += "font-size: 27px;\n";
  page += "}\n";
  page += ".form-group {\n";
  page += "margin-bottom: 5px;\n";
  page += "}\n";
  page += "}\n";
  page += "\n";
  page += "@media (max-width: 413px) {\n";
  page += ".main-content {\n";
  page += "text-align: center;\n";
  page += "}\n";
  page += "#alarm-form {\n";
  page += "font-size: 22px;\n";
  page += "}\n";
  page += ".form-group {\n";
  page += "margin-bottom: 8px;\n";
  page += "}\n";
  page += "}\n";
  page += ".start-bell {\n";
  page += "display: flex;\n";
  page += "justify-content: end;\n";
  page += "margin-right: 15px;\n";
  page += "}\n";
  page += "</style>\n";
  page += "</head>\n";
  return page;
}


String getBody() {
  String alarmData = getAlarmSd();

  String page = "<body>\n";
  page += "<div class=\"main-content\">\n";

  page += "</h1>\n";
  page += "<div id='date-time-server'></div>\n";

  page += "<button onclick='updateClock()' style='font-size: 24px;'><h4>Soatni kurish</h4></button>\n";
  
  page += "<h1>San'a va vaqt sozlash</h1>\n";
  page += "<form action=\"/setdatetime\" method=\"post\" onsubmit=\"return showConfirmation();\">\n";
  page += "<label for=\"date\">San'a (YYYY-MM-DD):</label>\n";
  page += "<input type=\"text\" id=\"date\" name=\"date\" required>\n";
  page += "<label for=\"hours\">Soatlar:</label>\n";
  page += "<input type=\"number\" id=\"hours\" name=\"hours\" min=\"0\" max=\"23\" step=\"1\" required>\n";
  page += "<label for=\"minutes\">Daqiqalar:</label>\n";
  page += "<input type=\"number\" id=\"minutes\" name=\"minutes\" min=\"0\" max=\"59\" step=\"1\" required>\n";
  page += "<label for=\"seconds\">Soniya:</label>\n";
  page += "<input type=\"number\" id=\"seconds\" name=\"seconds\" min=\"0\" max=\"59\" step=\"1\" required>\n";
  page += "<br>\n";
  page += "<input type=\"submit\" value=\"San'a va vaqt sozlash\">\n";
  page += "</form>\n";

  page += "<h1>Qo'ng'iroq Chalish Jadvalini Kiriting.</h1>\n";
  page += "<form method=\"POST\" id=\"alarm-form\">\n";
  page += "</form>\n";
  page += "</div>\n";


  page += "<script type=\"text/javascript\">\n";
  page += "let alarmSchedule = ";

  page += alarmData;
  

  page += "function clear_input_row(elem_index) {\n";
  page += "const inp = document.getElementById(`${elem_index}_al`);\n";
  page += "const minute = document.getElementById(`${elem_index}_al_minute`);\n";
  page += "const select = document.getElementById(`${elem_index}_len`);\n";
  page += "inp.value = \"\";\n";
  page += "minute.value = \"\";\n";
  page += "select.value = \"\";\n";
  page += "}\n";
  page += "function init_form() {\n";
  page += "let form = document.getElementById(\"alarm-form\");\n";
  page += "let form_html = \"\";\n";
  page += "\n";
  page += "for(let i = 1; i <=" + String(ALarmActualLen) +  "; i++) {\n";
  page += "let hour_val = parseInt(alarmSchedule[i + '_al_hour']) >= 0 ? alarmSchedule[i + '_al_hour'] : '';\n";
  page += "let min_val = parseInt(alarmSchedule[i + '_al_min']) >= 0 ? alarmSchedule[i + '_al_min'] : '';\n";
  page += "let len_val =  parseInt(alarmSchedule[i + '_len']) >= 0 ? alarmSchedule[i + '_len'] : '';\n";
  page += "let html = `\n";
  page += "<div class=\"form-group\">\n";
  page += "<h4>${i}chi Chalish vaqt.</h4>\n";
  page += "<div class=\"form-comp time-group\">\n";
  page += "<label for=\"${i}_al_hour\">Soat</label>\n";
  page += "<input name=\"${i}_al_hour\" id=\"${i}_al\" value=\"${hour_val}\" type=\"number\" min=\"0\" max=\"24\">\n";
  page += "\n";
  page += "<label for=\"${i}_al_min\">Daqiqa</label>\n";
  page += "<input name=\"${i}_al_min\" id=\"${i}_al_minute\" value=\"${min_val}\" type=\"number\" min=\"0\" max=\"60\">\n";
  page += "</div>\n";
  page += "\n";
  page += "<div class=\"form-comp\">\n";
  page += "<label for=\"${i}_len\">Davomiylik.</label>\n";
  page += "<select name=\"${i}_len\" id=\"${i}_len\">\n";
  page += "<option value=\"${len_val}\" selected>${len_val} ${len_val ? \"Soniya\" : \"\"}</option>\n";
  page += "<option value=\"2\">2 Soniya</option>\n";
  page += "<option value=\"3\">3 Soniya</option>\n";
  page += "<option value=\"5\">5 Soniya</option>\n";
  page += "<option value=\"10\">10 Soniya</option>\n";
  page += "<option value=\"30\">30 Soniya</option>\n";
  page += "</select>\n";
  page += "</div>\n";
  page += "\n";
  page += "<div class=\"form-comp\">\n";
  page += "<button class=\"clear-btn\" type=\"button\" onclick=\"clear_input_row(${i})\">Ma'lumotlarni tozalash.</button>\n";
  page += "</div>\n";
  page += "</div>\n";
  page += "`;\n";
  page += "form_html += html;\n";
  page += "}\n";
  page += "form_html += `<input type=\"submit\" value=\"Jadvalni Saqlash\" class=\"submit-btn\">`;\n";
  page += "form.innerHTML = form_html;\n";
  page += "}\n";
  page += "init_form();\n";

  page += "function updateClock() {";
  page += "var xhr = new XMLHttpRequest();\n";
  page += "xhr.onreadystatechange = function() {";
  page += "if (xhr.readyState === 4 && xhr.status === 200) {";
  page += "var currentTime = xhr.responseText;\n";
  page += "document.getElementById('date-time-server').textContent = currentTime;\n";
  page += "let [date, time] = currentTime.split(' ');\n";
  page += "time = time.split(':');\n";
  page += "document.getElementById('date').value = date;\n";
  page += "document.getElementById('hours').value = time[0];\n";
  page += "document.getElementById('minutes').value = time[1];\n";
  page += "document.getElementById('seconds').value = time[2];\n";
  page += "}";
  page += "};\n";
  page += "xhr.open('GET', '/gettime', true);\n";
  page += "xhr.send();\n";
  page += "}";
  // page += "setInterval(updateClock, 1000);";

  page += "function showConfirmation() {\n";
  page += "    var confirmation = window.confirm(\"Siz rostan-ham san'a va vaqtni sozlashga ishonchingiz komilmi?\");\n";
  page += "    if (confirmation) {\n";
  page += "        // Agar foydalanuvchi \"OK\" tugmasini bosingan bo'lsa, amalni bajarish uchun true qaytariladi\n";
  page += "        alert(\"San'a va vaqt muvaffaqiyatli sozlandi!\");\n";
  page += "        return true; // Formani jo'natishni davom ettirish uchun\n";
  page += "    } else {\n";
  page += "        // Agar foydalanuvchi \"Bekor qilish\" tugmasini bosingan bo'lsa, amalni bekor qilish uchun false qaytariladi\n";
  page += "        alert(\"San'a va vaqt sozlanmadi.\");\n";
  page += "        return false; // Formani jo'natishni bekor qilish uchun\n";
  page += "    }\n";
  page += "}\n";

  page += "</script>\n";
  
  
  page += "</body>\n";
  page += "</html>\n";
  return page;
}


String getIndexPage() {
  String page = getHeader();
  page += getBody();

  return page;
}
