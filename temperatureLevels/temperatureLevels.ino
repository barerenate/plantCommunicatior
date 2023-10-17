int sensePin = A0; //This is the Arduino Pin that will read the sensor output

void setup() {

Serial.begin(9600); //Start the Serial Port at 9600 baud (default)

}
void loop() {
int tempRead = analogRead(sensePin); //read the analog sensor and store it
float voltage = tempRead * (4.2 / 1024.0);
float temp = (voltage - 0.5) * 100; //Convert to degrees

Serial.print("Current Temperature: ");
Serial.println(temp);
delay(2000);
}
