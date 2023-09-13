#include "ArrayList.h"

int moistureSensor = A2;
double lightSensor = A3;
int tempSensor = A0; //This is the Arduino Pin that will read the sensor output
int tempInput; //The variable we will use to store the sensor input
double temp; //The variable we will use to store temperature in degrees.
ArrayList<double> lightValues; //arraylist to store light sensor data
double addedTemp = 0; //add Temperature on top of each other
bool belowZero = false;

void measure(int count){
  //double i = 0;

  while(count--){
     int rawMoistValue = analogRead(moistureSensor);
  int moisture = map(rawMoistValue, 0, 1023, 0, 100);

  tempInput = analogRead(A0); //read the analog sensor and store it
  temp = (double)tempInput / 1024; //find percentage of input reading
  temp = temp * 5; //multiply by 5V to get voltage
  temp = temp - 0.5; //Subtract the offset
  temp = temp * 100; //Convert to degrees

  // add temp to total temperature
  addedTemp =addedTemp + temp;

  // check if temperature is below 0 
  if (temp < 30){
    belowZero = true;
  }

  // Read raw data form phototransistor
  double rawLightValue = analogRead(lightSensor);
  // Change value range from 0-1023 (standard for analog read) to 0-100
  double light = map(rawLightValue, 0, 1023, 0, 100);
  // Display value in Serial Monitor
  
  Serial.println("-----------------------");
  Serial.print("Current Temperature: ");
  Serial.println(temp);

  Serial.print("Light level: ");
  Serial.println(light);

  Serial.print("Moisture: ");
  Serial.println(moisture);

  //storing the light sensore data in the arrayList
  lightValues.add(light);
  //i = i + 1;

  //measures every 5 seconds 
  delay(5000);
  }
}

void setup() {
  Serial.begin(9600);

  //amount of measurments (at the moment:36 so we have three minutes in total)
  int a = 36; //number of loops to measure 
  measure(a);

  // calculate the average temperature 
  double mean = addedTemp/a;


  //sort initial arrayList into three categories (sunny, bright/cloudy/shadow, dark)
  //Values still need to be corrected
  ArrayList<double> sunnyValues = lightValues.filter([](double n) -> bool{return n > 98;});
  ArrayList<double> shadowValues = lightValues.filter([](double n) -> bool{return n > 5 && n < 99;});
  ArrayList<double> darkValues = lightValues.filter([](double n) -> bool{return n < 5;});

  //check how many minutes the different light levels exist   

  //List of sunny Values
  double sunnyMin = sunnyValues.size() * 5;
  //List of shade Values
  double shadowMin = shadowValues.size() * 5;
  //List of dark Values
  double darkMin = darkValues.size() * 5;

  Serial.println("-----------------------");
  Serial.print("Seconds of sunshine: ");
  Serial.println(sunnyMin);

  Serial.print("Seconds of shade: "); //?? doesn't sound right
  Serial.println(shadowMin);

  Serial.print("Seconds of darkness: ");
  Serial.println(darkMin);

  Serial.print("Average temperature: ");
  Serial.println(mean);

  Serial.print("Was the temperature below zero? ");
  Serial.println(belowZero);


  }

  void loop() { 
}


