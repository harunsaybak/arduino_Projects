volatile int duty=0;

void setup() {
  // put your setup code here, to run once:
 DDRD |= (1 << 6);
 Serial.begin(9600);
 cli();
  OCR2A = 249;
  TCCR2A |= (1 << WGM21);
  TIMSK2 |= (1 << OCIE2A);
  TCCR2B |= (1 << CS22); // pr 64
  // 0.001 saniyede 1 ISR gir

 OCR0A = duty; // %50 duty cycle
 TCCR0A |= (1 << COM0A1); // none-inverting mode
 TCCR0A |= (1 << WGM01) | (1 << WGM00); // fast PWM Mode
 TCCR0B |= (1 << CS01); // prescaler 8
  sei();
}

volatile int i=0;
volatile int q=1; // parlaklık artma azaltma isareti
ISR(TIMER2_COMPA_vect)
{
  i++;
  if (i==100)
  {
    duty+=q*(256*5)/100;
    if(duty>255)
    {
      duty=255;
      q=-1;
    }
    else if (duty < 0)
    {
      duty=0;
      q=1;
    }

    i=0;
  }
  OCR0A=duty;
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(duty);


}
