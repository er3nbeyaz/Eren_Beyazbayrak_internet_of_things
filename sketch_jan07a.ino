#include "Air_Quality_Sensor.h" //Get the library
#include <Wire.h>
AirQualitySensor sensor(A0); //declare sensor

void setup(void) {
  // Join I2C has slave address 8
  Wire.begin(0x8);
  // call receiveEvent when data comes
  Wire.onRequest(requestEvent);
 
    Serial.begin(9600); //begin serial on 9600
    while (!Serial);  
    Serial.println("Waiting sensor to init...");
    delay(100); //delay to let sensors load
    
    if (sensor.init()) {
        Serial.println("READY!.");
        pinMode(13, OUTPUT);
        pinMode(12, OUTPUT);
        pinMode(11, OUTPUT);
        pinMode(10, OUTPUT);
        pinMode(9, OUTPUT);
    } else {
        Serial.println("Sensor ERROR!");
    }
}   //when ready print ready and declare LED as outputs or print an error 

void loop(void) {
    int quality = sensor.slope(); //get the quality value
    Serial.print("Sensor value: ");
    Serial.println(sensor.getValue());    //get value through serial
    digitalWrite(13, HIGH);
    if (quality == AirQualitySensor::FORCE_SIGNAL) {  //start the activation of pins
        Serial.println("EXTREME POLLUTION! Force signal active.");  //extreme blue light
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
    } else if (quality == AirQualitySensor::HIGH_POLLUTION) { //red light
        Serial.println("High pollution!");
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(9, LOW);
    } else if (quality == AirQualitySensor::LOW_POLLUTION) {    //amber light
        Serial.println("Low pollution!");
        digitalWrite(11, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
    } else if (quality == AirQualitySensor::FRESH_AIR) {    //green light
        Serial.println("Fresh air.");
        digitalWrite(12, HIGH);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        
    }

    delay(500);
}

void requestEvent(){    //create event that write the sensor value to bus
  Wire.write(sensor.getValue());
}
