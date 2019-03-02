volatile int sayi=0;
volatile bool cvr=0;
void setup() {

  pinMode(5,OUTPUT);
  cli();
  TCCR1B=0;
  TCCR1A=0;
  TCNT1=0;
  OCR1A=46874;
  TIMSK1|=(1<<OCIE1A);
  TCCR1B|=(1<<WGM12);
  TCCR1B|=(1<<CS12);
  sei();
  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect)
{
  sayi++;
  if(sayi==2)
  {
    cvr=1;
    sayi=0;
  }
}

void loop()
{
  while (cvr==1)
  {
   // Serial.println(cvr);
    digitalWrite(5,LOW);
  delay(2000);
    digitalWrite(5,HIGH);
  cvr=0;
  }
  
  
Serial.println(sayi);
  
}

