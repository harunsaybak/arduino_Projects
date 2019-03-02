int data;
int xi=0;
void setup() {

 Serial.begin(9600);
 DDRB|=(1<<1)|(1<<4)|(1<<5)|(1<<0)|(1<<3);
 pinMode(3,OUTPUT);

}

void loop() {
 
  
  if(Serial.available()>0){
   
    data=Serial.read();
   
    // a illeri yavas 61
    //b illeri normal 62
    //c illeri hızlı 63
    //d geri yvs 64 
    //e geri norm 65 
    //f geri hızlı 66
    //g sag 67
    // h sol 68

    if (data==0x61) {xi=50;

      PORTB&=~(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,xi);
// motor b
  PORTB&=~(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,xi);
  
    }
   else if (data==0x62 ) {xi=110;  
   PORTB&=~(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,xi);
// motor b
  PORTB&=~(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,xi);}
  
      else if (data==0x63 ) {xi=250;
        PORTB&=~(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,xi);
// motor b
  PORTB&=~(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,xi);
  }
      
    else if (data==0x64 ) {xi=50;

    PORTB|=(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,xi);
// motor b
  PORTB|=(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,xi);
        }
     else if (data==0x65 ) {xi=110;

    PORTB|=(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,xi);
// motor b
  PORTB|=(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,xi);
        }

      else if (data==0x66 ) {xi=250;

    PORTB|=(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,xi);
// motor b
  PORTB|=(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,xi);
        }
      
     
      else if (data==0x67 || data=='g') {
 
        PORTB&=~(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,40);
// motor b
  PORTB|=(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,80);
        
        }
      else if (data==0x68 || data=='h') {
         PORTB|=(1<<4);
  PORTB&=~(1<<1);
  analogWrite(3,80);
// motor b
  PORTB&=~(1<<5);
  PORTB&=~(1<<0);
  analogWrite(11,50);
        
        }
        else{  

   PORTB|=(1<<0)|(1<<1);
  
  
  } 

   
    }
  }
  

