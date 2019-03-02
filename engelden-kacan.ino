#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>



#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();
Adafruit_BNO055 bno2 = Adafruit_BNO055();
#define trigPin1 35
#define echoPin1 34

#define trigPin2 33
#define echoPin2 32

#define trigPin3 31
#define echoPin3 30

#define trigPin4 37
#define echoPin4 36

int kp=4;
int kd=10;
int lasterror=0;
int error=0;
int hiz; 

int mod1Cikis=0;
int gyroF=0;
int ii=0;
int dizi[13];
void setup()
{
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  
  
  pinMode(3,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);

    Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  bno.setExtCrystalUse(true);
   bno2.setExtCrystalUse(true);

  
}

  long sure, mesafe;
  int spd =0;
  int turev=0;
  int left,right;
  int orthiz=100;
  int ctr=0;
  int mod = 2;
  int aciDon=30;

   int sayac=0;
  void loop() {

   int mesafe_sol;
  int mesafe_on ;
  int mesafe_sag ;
  int mesafe_arka;
  
 /* while(!(sayac==5))
  {  
  mesafe_sol = engel(trigPin1,echoPin1);
  mesafe_on  = engel(trigPin2,echoPin2);
   mesafe_sag = engel(trigPin3,echoPin3);
  mesafe_arka= engel(trigPin4,echoPin4);
  Serial.print("---");
  Serial.println(mesafe_on);
  sayac++;
  }
  */
  
  mesafe_sol = engel(trigPin1,echoPin1);
  mesafe_on  = engel2(trigPin2,echoPin2);
   mesafe_sag = engel(trigPin3,echoPin3);
  mesafe_arka= engel(trigPin4,echoPin4);
 // gyroF=gyro(-1);
  Serial.print(gyroF);
  Serial.print("---");
  Serial.print(mesafe_sol);
  Serial.print("---");
  Serial.print(mesafe_on);
  Serial.print("---");
  Serial.print(mesafe_sag);
  Serial.print("---");
  Serial.println(mesafe_arka);

  if(mod == 0)
  {
    error = mesafe_sag-mesafe_sol;
    
    spd=kp*error + kd*turev ;
    
    turev=error-lasterror;
    lasterror=error;
    
    left  = orthiz + spd;
    right = orthiz - spd;
    if (left < 60 )
    {
      left =0;
    }
    if (right < 60 )
    {
      right =0;
    }
    if (left > 170 )
    {
      left =170;
    }
    if (right > 170 )
    {
      right =170;
    }
    
    
    baju(left,right);
    
    delay(50);
  }

  else if(mod == 1)
  {

    if (mesafe_sol>45)
    { 
      mod1Cikis++;
      mesafe_sol=20;
      if(mod1Cikis>2)
      {
        baju(80,80);
        delay(250);
        baju(150,30);
        delay(400);
        baju(90,90);
        delay(750);
        
        mod1Cikis=0;
       // mod=2;
      }
    }

    error = mesafe_sol-20;
    
    spd=kp*error + kd*turev ;
    
    turev=error-lasterror;
    lasterror=error;
    
    left  = orthiz + spd;
    right = orthiz - spd;
   
    if (left < 40 )
    {
      left =0;
    }
    if (right < 40 )
    {
      right =0;
    }
    if (left > 170 )
    {
      left =170;
    }
    if (right > 170 )
    {
      right =170;
    }
    
    
    baju(left,right);
    
  }

  else if(mod==2){

  // mesafe_on  = engel2(trigPin2,echoPin2);
   
   Serial.print("mod2   ");
   Serial.println(mesafe_on);
   while(mesafe_on>150)
   {
    
    baju(0,100);
    
    mesafe_on  = engel2(trigPin2,echoPin2);
    Serial.print("mod2   ");
    Serial.println(mesafe_on);
    //if(mesafe_on<199)
   // {
    //  ctr++;
    //  if(ctr<2)
    //  {
    //     mesafe_on=200;
    //  }
      
   // }
   delay(50);
   }
   mod=3;
    
  }

  else if(mod==3)
  {
    mesafe_on  = engel2(trigPin2,echoPin2);
    Serial.print("mod3   ");
    Serial.println(mesafe_on);
    
    while(mesafe_on>12)
    {
       Serial.print("mod3 WHİLE  ");
    Serial.println(mesafe_on);
    
       mesafe_on  = engel2(trigPin2,echoPin2);
      baju(80,80);
    }

    baju(30,150);
    delay(500);
    mod=1;
  }
 
  else
  {
    baju(0,0);
  }
}

int baju(int left, int right){

  analogWrite(11,left);
  analogWrite(3,right);
}
  
int engel(int trg, int echo){
    
  digitalWrite(trg, LOW);
  delayMicroseconds(2);
  digitalWrite(trg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trg, LOW);
  sure = pulseIn(echo, HIGH);
  mesafe = (sure/2) / 29.1;
     if (mesafe > 80  ){
     return 80;
     }
     else if(mesafe < 0)
     {
      return 0;
     }
     else {
     return mesafe;
     }
  }

int engel2(int trg, int echo){
    
  digitalWrite(trg, LOW);
  delayMicroseconds(2);
  digitalWrite(trg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trg, LOW);
  sure = pulseIn(echo, HIGH);
  mesafe = (sure/2) / 29.1;
     if (mesafe > 399  ){
     return 399;
     }
     else if(mesafe < 0)
     {
      return 0;
     }
     else {
     return mesafe;
     }
  }
