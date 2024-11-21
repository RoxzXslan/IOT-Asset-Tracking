#include <DFRobot_SIM808.h>
#include <string.h>

#define TX 10
#define RX 11
SoftwareSerial mySerial(TX, RX);
DFRobot_SIM808 sim808(&mySerial);


void getGPSdata(float& lat, float& lon) {
  while(!sim808.getGPS());
  lat = sim808.GPSdata.lat;
  lon = sim808.GPSdata.lon;
}

void setup() {

  Serial.begin(9600);

  mySerial.begin(9600);

  // Initialising SIM808 Module
  while(!sim808.init()){
    delay(1000);
    Serial.print("Sim808 init error\r\n");
  }
  // Turning ON GPS
  if(sim808.attachGPS())
    Serial.println("Open the GPS power success");
  else 
    Serial.println("Open the GPS power failure");
}

void loop() {
  float lat, lon;
  getGPSdata(lat, lon); // Getting GPS data - latitude, longitude
  
  String out = "Latitude:"+String(lat)+",Longitude:"+String(lon);
  Serial.println(out);

}
