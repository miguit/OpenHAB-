#include <OneWire.h>
#include <VirtualWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A4
int calibrationTime = 30;
//the time when the sensor outputs a low impulse
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;

int pirPin = 5;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
char temp[6];

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  vw_setup(2000);
  vw_set_tx_pin(8);
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  delay(50);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  float t = sensors.getTempCByIndex(0);
  char id[10] = "Sensor1|";
  dtostrf(t, 5, 2, temp);
  strcat(id, temp);
  vw_send((uint8_t *)id, strlen(id));
  vw_wait_tx();
  delay(4000);

  if (digitalRead(pirPin) == HIGH) {
    digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
      char pir[5] = "pir1";
  vw_send((uint8_t *)id, strlen(pir));
  vw_wait_tx();
  delay(2000);
    if (lockLow) {
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false;

      delay(50);
    }
    takeLowTime = true;
  }

  if (digitalRead(pirPin) == LOW) {
    digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

    if (takeLowTime) {
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
    //if the sensor is low for more than the given pause,
    //we assume that no more motion is going to happen
    if (!lockLow && millis() - lowIn > pause) {
      //makes sure this block of code is only executed again after
      //a new motion sequence has been detected
      lockLow = true;
      delay(50);
    }
  }
}
