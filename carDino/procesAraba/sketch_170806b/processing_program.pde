/*
**farenin sol tuşu sola ,sağ tuş sağa
**orta tekerlek ile illeri geri sürülür
**herhangi bir tuş fren tuşudur ama fren etkinken sağa yada sola sürülebilir
*/
import processing.serial.*;
Serial myPort;
float e; // kullandığınız mouse göre değeri çok artabilir yada 2 ye bile zor gelebilir
// kandi farenize göre if ' lerin içini doldurun
PImage img; // illeir
PImage ger;
PImage sol;
PImage sag;
void setup() {   
  
  size(330,300);
  img = loadImage("illeri.png");
  ger = loadImage("geri.png");
  sol = loadImage("sola.png");
  sag = loadImage("saga.png");
myPort=new Serial(this,Serial.list()[0],9600);
}

void mouseWheel(MouseEvent event) {
   e = event.getCount();
  println(e);
  
}
int i=0;
int illeri=0;


void draw() {
  noStroke();
  
  background(255,204,0);
  image(img,width/2-20,height/2-90,60,60);
  image(ger,width/2-20,height/2+40,60,60);
  image(sol,width/2-100,height/2-20,60,60);
  image(sag,width/2+60,height/2-20,60,60);
  
  if(e>0 && i==0) { 
    rect(width/2-15,height/2-85,50,50);
    fill(#f825d8,90);
    
  myPort.write(0x62);
  }
  
  else if(e<0 && i==0) {  rect(width/2-15,height/2+45,50,50);
    fill(#ff00ff,90);
myPort.write(0x65);
}

}


void mousePressed() {
  if (mouseButton == RIGHT) { 
    rect(width/2-100,height/2-20,60,60);
    fill(#ff00dd,90);
    myPort.write(0x67);
  } else if (mouseButton == LEFT) { 
  rect(width/2+60,height/2-20,60,60);
   fill(#ffffff,90);
     myPort.write(0x68);
  } 
}
void mouseReleased() {
   
    
  myPort.write(0x6A); 
  
}
void keyPressed() { 
   i=~i;
    myPort.write(0x6A);
}