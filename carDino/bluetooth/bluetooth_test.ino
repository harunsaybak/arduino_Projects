#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6);
// TX, RX


void setup() {
mySerial.begin(9600);
Serial.begin(9600);
}
void loop() {
  
  if(mySerial.available()>0){
  char ch = mySerial.read();
 Serial.println(ch);
  }
}
