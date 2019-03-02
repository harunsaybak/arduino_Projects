#include <TM1637Display.h>

#include "TM1637.h"  

#define CLK 3
#define DIO 2

TM1637Display disp(CLK,DIO);

void setup()
{
  disp.set(5);
  disp.init(D4056A);
}

void loop() {
  int v=1;

  
  disp.display(500);
  delay(1000);
  v=v+1;
  }
}
