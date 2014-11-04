#include <VirtualWire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 13

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int i;
void setup(){
// setup OW sensors
  sensors.begin();
// setup VirtualWire 
  vw_set_rx_pin(3);  
  vw_set_tx_pin(2);
  vw_set_ptt_pin(1);// without this not working with lcd shield
  vw_setup(2000);
  vw_rx_start();
//setup lcd
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("press select");
//setup serial connection
  Serial.begin(9600);
}
void loop(void){
  String str;
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  //get RF serial message
  if( vw_get_message(buf, &buflen) )
  {
    lcd.setCursor(0, 0);
    for (i = 6; i < buflen; i++){
      //Serial.print(char(buf[i]));
      str += char(buf[i]);
    }
    if (i>=buflen){
      Serial.println("");
      Serial.println(str);
      lcd.print(str);
      sensors.requestTemperatures();
      lcd.setCursor(0, 1);
      int numberOfDevices = sensors.getDeviceCount();
      Serial.print("OWDevices:");
      Serial.println(numberOfDevices); // Why "byIndex"? 
      int c = 0;
      for (c = 0; c < numberOfDevices; c++){
        String item = "OW";
        item +=c;
        item +=":";     
        Serial.print(item);
        Serial.println(sensors.getTempCByIndex(c)); // Why "byIndex"? 
        lcd.print(sensors.getTempCByIndex(c));
      }
      delay(10000);
    }
  }
}
