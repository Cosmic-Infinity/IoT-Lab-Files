


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid     = "Testing ESP8266";
const char* password = "123456789";

#define result 14     // Digital pin connected to the DHT sensor

String t = "";// current state updated in loop()
AsyncWebServer server(80);// Create AsyncWebServer object on port 80
unsigned long previousMillis = 0;    // will store last time DHT was updated

// Updates DHT readings every 'interval' miliseconds
const long interval = 100;  

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>HW-201 Proximity State</h2>
  <p align="center">
    <span class="dht-labels">Current State : </span> 
    <span id="state">%STATE%</span>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/state", true);
  xhttp.send();
}, 100 ) ;
</script>
</html>)rawliteral";

String processor(const String& var){
  //Serial.println(var);
  if(var == "STATE"){
    return String(t);
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  //dht.begin();
  
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  Serial.println(WiFi.localIP()); // Print ESP8266 Local IP Address

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(t).c_str());
  });
  

  // Start server
  server.begin();
}
 
void loop(){  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;// save the last time you updated the DHT values
    if( digitalRead(result) == LOW){
      t = digitalRead(result);
      Serial.println("Detected");
    }
    else{
      t = digitalRead(result);
      Serial.println("NOT Detected");
    }
  }
}