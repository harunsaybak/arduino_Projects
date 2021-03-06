#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>



#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();

int gyroF=0;
void setup() {
  // put your setup code here, to run once:

   Serial.begin(115200);
    Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  bno.setExtCrystalUse(true);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  gyroF =euler.x();

  Serial.println(gyroF);

}
