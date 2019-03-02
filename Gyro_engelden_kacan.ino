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
  
  int mod = 2;
  int aciDon=30;  
  void loop() {
    
  int mesafe_sol = engel(trigPin1,echoPin1);
  int mesafe_on  = engel(trigPin2,echoPin2);
  int mesafe_sag = engel(trigPin3,echoPin3);
  int mesafe_arka= engel(trigPin4,echoPin4);

  gyroF=gyro(-1);
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

    
    dizi[ii] = mesafe_on;
    Serial.println(dizi[ii]);
    ii+=1;
    gyro(aciDon);
    aciDon+=30;

    if(ii == 12)
    {
      mod=3;
    }
    
  }

  else if (mod==3)
  {
    int index = 0;
    int temp = dizi[0];
    for(int i=1; i<13; i++){
         if(dizi[i]<temp){
           temp = dizi[i];
           index = i;
         }
    }

    gyro(index*30);
    
    while(1)
    {
      baju(0,0);
    }
    
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


int gyro(int aci)
{  
   imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
     gyroF =euler.x();
     //Serial.print("ilk gyro   ");
     //Serial.println(gyroF);
     
   if(aci == -1)
   {
     
     return gyroF;
   }

   else
   {
      while(!(gyroF<aci+5 && gyroF>aci-5))
      {
        imu::Vector<3> euler = bno2.getVector(Adafruit_BNO055::VECTOR_EULER);
        gyroF =euler.x();
        //Serial.println(gyroF);
        baju(0,100);
      }
   }

}
  
