#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


#include <QTRSensors.h>
#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   42    // emitter is controlled by digital pin 2


// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {49, 47, 45, 43, 41, 39, 37, 35},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];


#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();

const int motor_A_direction = 13; // sol motor
const int motor_B_direction = 12; // sag motor
//const int motor_B_fren = 8;
//const int motor_A_fren = 9;
const int motor_A_speed = 11;
const int motor_B_speed = 3;
int M1_minumum_speed = 90;    //minimum speed of the Motor1
int M2_minumum_speed = 90;  //minimum speed of the Motor2
int M1_maksimum_speed = 140; //max. speed of the Motor1
int M2_maksimum_speed = 140; //max. speed of the Motor2

float KP = 0.06;
float KD = 0.25; //Eger cizgiyi takip edebiliyorsak artik kd degerini 1 yap. salinim azalana kadar bu degeri arttirmaya devam et. Deger ondalik sayi olabilir.
float KI = 0.0;/*Eger robot cizgiyi kararli bir sekilde takip ediyorsa, bu degere 1-0.5 arasinda bir deger ver. Ki degeri cok yuksek ise robot cok hizli salinim yapacaktir.
               eger deger cok dusukse herhangi bir hissedilir fark goremeyeceksin. Sayi az az arttirilmalidir.                 */
int flag = 0;

float lastError = 0;
float integral = 0;


char ifim='a';
int sol=0;
int sag=0;
int position2;

float gyroF =0;
float gyroT = 0; 

void setup()
{
 // DDRD |=(1<<3);
  pinMode(3,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,INPUT_PULLUP);   
  pinMode(28,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(A15,INPUT);
  pinMode(A14,INPUT);
 // DDRB |= (1 << 3) | (1<<4)|(1<<5);
 
    Serial.begin(115200);
    Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

   if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  bno.setExtCrystalUse(true);

  
    qtrrc.calibrate();       
 
        qtrrc.calibratedMinimumOn[0]=96;
        qtrrc.calibratedMinimumOn[1]=132;
        qtrrc.calibratedMinimumOn[2]=96;
        qtrrc.calibratedMinimumOn[3]=92;
        qtrrc.calibratedMinimumOn[4]=132;
        qtrrc.calibratedMinimumOn[5]=132;
        qtrrc.calibratedMinimumOn[6]=180;
        qtrrc.calibratedMinimumOn[7]=180;
    
  Serial.println();

    qtrrc.calibratedMaximumOn[0]=2500;
    qtrrc.calibratedMaximumOn[1]=2500;
    qtrrc.calibratedMaximumOn[2]=2500;
    qtrrc.calibratedMaximumOn[3]=2500;
    qtrrc.calibratedMaximumOn[4]=2500;
    qtrrc.calibratedMaximumOn[5]=2500;
    qtrrc.calibratedMaximumOn[6]=2500;
    qtrrc.calibratedMaximumOn[7]=2500;

  Serial.println();
  Serial.println();

  hiz(0, 0);
  delay(500);
  digitalWrite(13,HIGH);
  digitalWrite(12,HIGH);
  int sw=digitalRead(7);
  while(sw==1)
  {
    sw=digitalRead(7);
  }

   
}


volatile int ss=0; 
volatile int Zss=0;
volatile int zaman=0;
volatile int zaman2=0;
void loop()
{  
   sol=analogRead(A15);
   sag=analogRead(A14);
      
   
  //Serial.print(sol);
 // Serial.print('\t');
  //Serial.println(sag);
  

  int position = qtrrc.readLine(sensorValues);

  int error = position - 3500; // 3500 değeri, sensörlerin çizgiyi tamamen ortaladığında okunan position değeridir.
 ;

   imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

   
   if(sol > 600 && sag<400)
   {
    
    ss=1;
    Zss=millis();
   // hiz(0,0);
   // delay(50);
   }
   
   else if (sag > 600 && sol<400)
   {
    
    ss=2;
    Zss=millis();
   // hiz(0,0);
   // delay(50);
   }
   
   int suan=millis();
   
   if ((ss==1 || ss==2) && suan-Zss>1000)
   {
    ss=0;
   }

   if ( ss=1 && sensorValues[7]>500 && sensorValues[6]>500 && sensorValues[5]>500 && sensorValues[4]>400 && sensorValues[0]<250 && sensorValues[1]<250) // sola don
   {
    hiz(0,0);
    delay(150);
    position2 = qtrrc.readLine(sensorValues);
    if (position2>6500 || position2<500)
    {
    zaman2=millis();
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    
    digitalWrite(28,HIGH);
    while(zaman-zaman2<250)
    { 
      hiz(150, 65);
      zaman=millis();
    }
    
    digitalWrite(28,LOW);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH); 
   }
   }
   
   else if (ss=2 && sensorValues[0]>500 && sensorValues[1]>500 && sensorValues[2]>500 && sensorValues[3]>400 && sensorValues[7]<250 && sensorValues[6]<250)
   {
    hiz(0,0);
    delay(150);
    position2 = qtrrc.readLine(sensorValues);
    if (position2>6500 || position2<500)
    {
    zaman2=millis();
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    
    digitalWrite(26,HIGH);
    while(zaman-zaman2<250)
    { 
      hiz(65, 150);
      zaman=millis();
    }
    
    digitalWrite(26,LOW);
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH); 
    }
   }
   
  gyroT = euler.x() - gyroF ;
  integral = integral + error;
  float turev = error - lastError; 

   if(gyroT>300 || gyroT < -300)
  {
    gyroT = 2;
    
  }

  float oran=KP * error;
  float td=KD * turev;
  float gyroY = gyroT * 3.5;
  int motorSpeed =  oran + td + (KI * integral) + gyroY;
  lastError = error;
  int leftMotorSpeed ;
  gyroF =euler.x();
  if(M1_minumum_speed - motorSpeed > 0)
  {
     leftMotorSpeed = M1_minumum_speed - motorSpeed;
  }
  else
  {
     leftMotorSpeed = 0;
  }
 

  int rightMotorSpeed ;
  if(  M2_minumum_speed + motorSpeed >0)
  {
   rightMotorSpeed = M2_minumum_speed + motorSpeed;
    
  }
  else
  {
    rightMotorSpeed = 0;
  }
   if(leftMotorSpeed > M1_maksimum_speed)
  {
    
     leftMotorSpeed = M1_maksimum_speed;
  }
  if(rightMotorSpeed > M1_maksimum_speed )
  {
    
     rightMotorSpeed = M1_maksimum_speed;
  }

  int inL = abs(gyroT)*20;
  int inR = abs(gyroT)*20;
  if (leftMotorSpeed-inL <0)
  {
    inL=0;
  }
  
  if (rightMotorSpeed-inR <0)
  {
    inR=0;
  }
  hiz(leftMotorSpeed-inL,rightMotorSpeed-inR);

  Serial.print(sol);
    Serial.print('\t');
     Serial.print(sag);
     Serial.print('\t');
     Serial.print('\t');
     Serial.print(leftMotorSpeed);
     Serial.print('\t');
     Serial.print(leftMotorSpeed-inL);
     Serial.print('\t');
     Serial.print(rightMotorSpeed);
     Serial.print('\t');
     Serial.print(rightMotorSpeed-inR);
     Serial.print('\t');
     Serial.print(abs(gyroT));
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    digitalWrite(26,LOW);
    digitalWrite(28,LOW);

/*  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  //Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
  
  Serial.println();
  */
  
}


void hiz(int speed_a, int speed_b)
{
  analogWrite(motor_A_speed, speed_a);
  analogWrite(motor_B_speed, speed_b);
}
