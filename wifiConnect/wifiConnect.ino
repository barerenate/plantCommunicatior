// Sources:
// Moisturesensor: https://arduinogetstarted.com/tutorials/arduino-soil-moisture-sensor
// Lightsensor: https://www.youtube.com/watch?v=qKku-mmwNIA
// Temperaturesensor: https://lastminuteengineers.com/tmp36-temperature-sensor-arduino-tutorial/
// Wificonnection and web-server: https://arduinogetstarted.com/tutorials/arduino-web-server

#include "WiFiS3.h"
#include "index.h"

char ssid[] = "Testnett";        // your network SSID (name)
char pass[] = "Hahalmao";    // your network password

int status = WL_IDLE_STATUS;
WiFiServer server(80);

int tempPin = A0;
int moistPin = A2;
int lightPin = A3;

int moistThreshold = 2;

float getTemp() {
  int tempRead = analogRead(tempPin); //read the analog sensor and store it
  float voltage = tempRead * (5.0 / 1024.0);
  float temp = (voltage - 0.5) * 100; //Convert to degrees
  return temp;
}

int getMoisture() {
  int moistRead = analogRead(moistPin);
  int moisture = map(moistRead, 0, 1023, 0, 100);

  return moisture;
}

String checkMoistThresh(int x) {
  int moisture = x;

  if (moisture < moistThreshold)
    return "Plant needs water";
  else
   return "Plant is happy :)";

}

int getLightLevel() {
  int lightRead = analogRead(lightPin);
  int light = map(lightRead, 0, 1023, 0, 100);
  return light;
}

void setup() {
  Serial.begin(9600);
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  server.begin(); // start the web server on port 80
  printWifiStatus(); // you're connected now, so print out the status
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    // read the HTTP request header line by line
    while (client.connected()) {
      if (client.available()) {
        String HTTP_header = client.readStringUntil('\n');  // read the header line of HTTP request

        if (HTTP_header.equals("\r"))  // the end of HTTP request
          break;

        Serial.print("<< ");
        Serial.println(HTTP_header);  // print HTTP request to Serial Monitor
      }
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  // the connection will be closed after completion of the response
    client.println();                     // the separator between HTTP header and body

    float currentTemp = getTemp();
    int currentMoisture = getMoisture();
    int currentLightLevel = getLightLevel();

    String moistureCheck = checkMoistThresh(currentMoisture);


    String html = String(INDEX_HTML);
    html.replace("tempMarker", String(currentTemp));
    html.replace("moistureMarker", String(currentMoisture));
    html.replace("lightMarker", String(currentLightLevel));
    html.replace("statusMarker", String(moistureCheck));
    client.println(html);
    client.flush();

    // give the web browser time to receive the data
    delay(10);

    // close the connection:
    client.stop();
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}