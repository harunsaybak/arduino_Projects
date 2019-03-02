// belli bir surede bir ledi yakip sondurur
void setup()
{
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1=0;
  OCR1A=62499;
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
   sei();
}

volatile bool state=0;
ISR(TIMER1_COMPA_vect) {
state=!state;
  
}

void loop()
{
  Serial.println(state);
  digitalWrite(7,state);
 
}
