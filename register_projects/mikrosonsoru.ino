void setup() {
  
Serial.begin(9600);
cli();
//timer1 1Hz' e ayarlanıyor
    //registerler sıfırlanır
    TCCR1A = 0;// TCCR1A register 0'lanıyor
    TCCR1B = 0;// TCCR1B register 0'lanıyor
    TCNT1  = 0;//sayac değeri  0'la
 // OCRxA karşılaştırma registeri 1Hz değer için ayarlanıyor
  //16 MHz osilatör,1Hz timer1 ın çalışma frekansı,1024 prescalar
    OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (değer 65536 dan küçük)
//   CTC mod açılıyor.
    TCCR1B |= (1 << WGM12);
  //   CS10 ve CS12 bitleri 1024 prescaler için ayarlanıyor
    TCCR1B |= (1 << CS12) | (1 << CS10);  
  // timer karşılaştırma interruptı aktifleştiriliyor
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

int i,j,k,q;

void loop() {

q=hiz();
}



int hiz(){

if(k==1){ // sinyal gönderilmişse
   pinMode(7,INPUT); // pinden veri al
   while(digitalRead(7)==LOW); // veri 0 sa bekle
   j=millis(); // veri geldi zamanı j'ye ata
   while(digitalRead(7)==HIGH); // veri akışı bitene dek bekle
   q=millis()-j;// veri akışı bitti zaman farkını q ye ata
   
   k=0; // tekrar sinyal gönderimine hazır
  }
return(q); // q yü döndür
}

ISR(TIMER1_COMPA_vect){ 
    // tetikleyici sinyali gönder
     pinMode(7,OUTPUT); // pine sinyal gönder
     digitalWrite(7,HIGH);
     delay(20);
     digitalWrite(7,LOW);
     delay(20);
     digitalWrite(7,HIGH);
     delay(20);
     digitalWrite(7,LOW);
   // sinyal gönderildi
  k=1; // sinyali gönderildiğinin göstergesi
  }
