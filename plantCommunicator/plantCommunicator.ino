int moistureSensor = A2;
int lightSensor = A3;
int tempSensor = A0; //This is the Arduino Pin that will read the sensor output
int tempInput; //The variable we will use to store the sensor input
double temp; //The variable we will use to store temperature in degrees.

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawMoistValue = analogRead(moistureSensor);
  int moisture = map(rawMoistValue, 0, 1023, 0, 100);

  tempInput = analogRead(A0); //read the analog sensor and store it
  temp = (double)tempInput / 1024; //find percentage of input reading
  temp = temp * 5; //multiply by 5V to get voltage
  temp = temp - 0.5; //Subtract the offset
  temp = temp * 100; //Convert to degrees

  // Read raw data form phototransistor
  int rawLightValue = analogRead(lightSensor);
  // Change value range from 0-1023 (standard for analog read) to 0-100
  int light = map(rawLightValue, 0, 1023, 0, 100);
  // Display value in Serial Monitor
  
  Serial.println("-----------------------");
  Serial.print("Current Temperature: ");
  Serial.println(temp);

  Serial.print("Light level: ");
  Serial.println(light);

  Serial.print("Moisture: ");
  Serial.println(moisture);

  delay(3000);
}
