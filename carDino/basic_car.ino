int motor_A_yon  = 12;
int motor_A_fren =  9;
int motor_A_hiz  =  3;
int motor_B_yon  = 13;
int motor_B_fren =  8;
int motor_B_hiz  = 11;

int left_arrow = 37;
int up_arrow = 38;
int right_arrow = 39;
int down_arrow = 40;

void fren(int motor_A_fren, int motor_B_fren) {
  digitalWrite(motor_A_fren, HIGH);
  digitalWrite(motor_B_fren, HIGH);
}
void hiz(int hiz_) {
  analogWrite(motor_A_hiz, hiz_);
  analogWrite(motor_B_hiz, hiz_);
}
void ileri() {
  digitalWrite(motor_A_yon, HIGH);
  digitalWrite(motor_B_yon, HIGH);

  digitalWrite(motor_A_fren, LOW);
  digitalWrite(motor_B_fren, LOW);
}
void geri() {
  digitalWrite(motor_A_yon, LOW);
  digitalWrite(motor_B_yon, LOW);

  digitalWrite(motor_A_fren, LOW);
  digitalWrite(motor_B_fren, LOW);
}

void sag() {
  digitalWrite(motor_A_yon, LOW);
  digitalWrite(motor_B_yon, HIGH);

  digitalWrite(motor_A_fren, LOW);
  digitalWrite(motor_B_fren, LOW);
}

void sol() {
  digitalWrite(motor_A_yon, HIGH);
  digitalWrite(motor_B_yon, LOW);

  digitalWrite(motor_A_fren, LOW);
  digitalWrite(motor_B_fren, LOW);
}
void setup() {
  // A ve B motoru icin fren ve yon pinleri output olarak ayarlandi.
  Serial.begin(9600);
DDRB|=(1<<0)|(1<<1)|(1<<4)|(1<<5); 
 pinMode(3,OUTPUT);

}

void loop() {
  hiz(200);
int veri = Serial.read();
if(veri == up_arrow){
  ileri();
}
else if(veri == down_arrow){
  geri();
}
else if(veri == right_arrow){
  sag();
}
else if(veri == left_arrow){
  sol();
}
}
