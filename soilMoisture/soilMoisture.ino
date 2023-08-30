int sensor = A2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw_value = analogRead(sensor);
  int moisture = map(raw_value, 0, 1023, 0, 100);

  Serial.print("Moisture: ");
  Serial.println(moisture);

  delay(2000);
}

