#include "WiFiS3.h"
#include "index.h"
#include "ArrayList.h"

char ssid[] = "AndroidAP";        // your network SSID (name)
char pass[] = "glye5160";    // your network password

int status = WL_IDLE_STATUS;
WiFiServer server(80);

int tempPin = A0;
int moistPin = A2;
int lightPin = A3;

ArrayList<int> lightValues; //arraylist to store light sensor data
int addedTemp = 0; //add temperature on top of each other
int addedLight = 0; //add light levels on top of each other
int addedMoist = 0; //add moisture levels on top of each other
int counter = 0;

int getTemp() {
  int tempRead = analogRead(tempPin); //read the analog sensor and store it
  float voltage = tempRead * (4.1 / 1024.0);
  float temp = (voltage - 0.5) * 100; //Convert to degrees
  return temp;
}

int getMoisture() {
  int moistRead = analogRead(moistPin);
  int moisture = map(moistRead, 0, 1023, 0, 100);
  return moisture;
}

int getLightLevel() {
  int lightRead = analogRead(lightPin);
  int light = map(lightRead, 0, 1023, 0, 100);
  return light;
}

String checkMoistThresh(int x) {
  int moisture = x;
  int moistThreshold = 10;

  if (moisture < moistThreshold)
    return "Plant needs water";
  else
   return "Plant is happy :)";

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

    delay(1000);
  }
  server.begin(); // start the web server on port 80
  printWifiStatus(); // you're connected now, so print out the status
}


void loop() {
  Serial.println("-----------------------");
  Serial.print("Current Temperature: ");
  Serial.println(getTemp());

  Serial.print("Light level: ");
  Serial.println(getLightLevel());

  Serial.print("Moisture: ");
  Serial.println(getMoisture());

  //storing the light sensore data in the arrayList
  lightValues.add(getLightLevel());
  //i = i + 1;

  //measures every second
  delay(1000);

  addedTemp = addedTemp + getTemp();
  addedLight = addedLight + getLightLevel();
  addedMoist = addedMoist + getMoisture();
  counter++;

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


  // calculate the average temperature 
  int meanTemp = addedTemp/counter;

  // calculate the average light level 
  int meanLight = addedLight/counter;
  
  // calculate the average moisture
  int meanMoist = addedMoist/counter;

  // current light level from sensor
  int currentLight = getLightLevel();

  // current temp
  int currentTemp = getTemp();

  // current moist
  int currentMoist = getMoisture();

  // calling the warning message 
  checkMoistThresh(currentMoist);



  //sort initial arrayList into three categories (sunny, bright/cloudy/shadow, dark)
  //Values still need to be corrected
  ArrayList<int> sunnyValues = lightValues.filter([](int n) -> bool{return n > 94;});
  ArrayList<int> shadowValues = lightValues.filter([](int n) -> bool{return n > 5 && n < 95;});
  ArrayList<int> darkValues = lightValues.filter([](int n) -> bool{return n < 5;});

  //check how many minutes the different light levels exist   

  //List of sunny Values
  int sunnyMin = sunnyValues.size()/60;
  //List of shade Values
  int shadowMin = shadowValues.size()/60;
  //List of dark Values
  int darkMin = darkValues.size()/60;

    
    String html = String(INDEX_HTML);
    html.replace("lightMarker", String(currentLight));
    html.replace("sunnyMarker", String(sunnyMin));
    html.replace("shadeMarker", String(shadowMin));
    html.replace("darknessMarker", String(darkMin));
    html.replace("moistureMarker", String(currentMoist));
    html.replace("tempMarker", String(currentTemp));
    html.replace("meanTempMarker", String(meanTemp)); 
    html.replace("meanLightMarker", String(meanLight)); 
    html.replace("meanMoistMarker", String(meanMoist)); 
    html.replace("timeMarker", String(counter)); 
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