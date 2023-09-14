// Choosing input pin (?)
int lightSensor = A3;

void setup() {
  // Starting communication between board and pc
  Serial.begin(9600);
}

void loop() {
  // Read raw data form phototransistor
  int raw_value = analogRead(lightSensor);
  // Change value range from 0-1023 (standard for analog read) to 0-100
  int light = map(raw_value, 0, 1023, 0, 100);
  // Display value in Serial Monitor
  Serial.print("Light level: ");
  Serial.println(light);
  // Update rate in miliseconds
  delay(2000);
}
