#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6);
// TX, RX

void setup() {
pinMode(4,OUTPUT);      
pinMode(10,OUTPUT);
mySerial.begin(9600); 
digitalWrite(10,HIGH);


}
bool durum = 0;
int surat = 100;
void loop() {
//int hiz2=surat-surat/2;

  char ch = mySerial.read();

  
if(ch == 'q'){
  durum =! durum;

  digitalWrite(4,durum);
}

  if(ch == 'x'){
surat=127;

  }

  if(ch == 't'){
surat=255;

  }
  
  if(ch == 'k'){

surat=surat+20;
  }

if(ch == 'r'){

surat=surat-20;
  }
  
  if(ch ==  'a'){
 ileri(surat);
  }

  else if(ch == 'b'){
   sol(surat,60);
  }

  else if(ch == 'c'){
sag(surat,60);
    
  }

  else if(ch == 'd'){

    geri(surat);
  }
  else if(ch == 'e'){

    dur();
  }
    else {

    }
  }
  

int geri(int hiz){ // araba geri gider

  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  analogWrite(3,hiz); 
  analogWrite(11,hiz);

}

int ileri(int hiz){ // araba ileri gider
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  analogWrite(3,hiz);
  analogWrite(11,hiz);
 
}
int sag(int hiz, int hiz2){ // araba sola döner
analogWrite(12,HIGH);
analogWrite(13,HIGH);
analogWrite(3,hiz);
analogWrite(11,hiz2);

}

int sol(int hiz,int hiz2){ //araba saga döner
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
analogWrite(3,hiz2);
analogWrite(11,hiz);

}

int dur(){ // araba durur
  analogWrite(3,0);
analogWrite(11,0);
}
