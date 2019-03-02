//analog veri okuma
volatile int ch=2;
void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
ADMUX=(ADMUX & 0xF8)|ch;
ADMUX|=(1<<REFS0);
ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);


}
volatile int i;
void loop() {
  // put your main code here, to run repeatedly:

ADCSRA|=(1<<ADSC);
while(ADCSRA & (1<<ADSC));
i=ADC;
Serial.println(i);

}
