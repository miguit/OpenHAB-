#include <VirtualWire.h>
#include "DHT.h"

#define DHTPIN 7     // what pin we're connected to
//#define ONE_WIRE_BUS 2
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

char temp[6];
char hum[6];

void setup() {

  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(3);
  dht.begin();

}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  char id[9] = "Sensor1|";
  char mark[2] ="|";
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  dtostrf(t, 5, 2, temp);
  dtostrf(h, 5, 2, hum);
  strcat(id,temp);
  strcat(id,mark);
  strcat(id,hum);
  strcat(id,mark);
  
  Serial.print(id);
  Serial.print("\n");
  vw_send((uint8_t *)id, strlen(id));

  vw_wait_tx();

  delay(200);

}
