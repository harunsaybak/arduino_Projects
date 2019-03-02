// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <TM1637Display.h>
 
const int CLK = 9; //Set the CLK pin connection to the display
const int DIO = 8; //Set the DIO pin connection to the display
 
int numCounter = 0;
int hmt = 0; 
bool ses=0;

TM1637Display display(CLK, DIO); //set up the 4-Digit Display.


#define DHTPIN            12         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
volatile long sayi=0;
void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  analogWrite(6,0);
  Serial.begin(9600); 
  // Initialize device.
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  display.setBrightness(0x0a); 


  cli();
  TCCR1B=0;
  TCCR1A=0;
  TCNT1=0;
  OCR1A=46874;
  TIMSK1|=(1<<OCIE1A);
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS12);
  sei();
}
volatile bool cvr=0;
ISR(TIMER1_COMPA_vect)
{
  sayi++;
  if(sayi==7200)
  {
    cvr=1;
  }
}


void loop() {

  while (cvr == 1)
  {
    digitalWrite(5,HIGH);
    delay(15000);
    cvr=0;
  }
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
   
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    hmt=event.relative_humidity;
    Serial.print("Humidity: ");
    Serial.print(hmt);
    Serial.println("%");
    display.showNumberDec(hmt);
  }

  
  if((hmt > 78 || hmt<55) && ses==0 )

  {
    pinMode(6,OUTPUT);
    analogWrite(6,200);
    
  }
  else
  {
    pinMode(6,INPUT);
    if (hmt<79 && hmt>54)
    {
      ses=0;
    }
  }

  int tus=digitalRead(2);
  if((hmt > 78 || hmt<55) && tus==0)
  {
    ses=1;
  }

}
