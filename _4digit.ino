#include <TM1637Display.h>

const int CLK = A1; //Set the CLK pin connection to the display
const int DIO = A0; //Set the DIO pin connection to the display
 
int numCounter = 0;
 
TM1637Display display(CLK, DIO); //set up the 4-Digit Display.
 
void setup()
{
display.setBrightness(0x0a); //set the diplay to maximum brightness
}
 
 
void loop()
{
for(numCounter = 0; numCounter < 9999; numCounter++) //Iterate numCounter
{
display.showNumberDec(numCounter); //Display the numCounter value;
delay(5);
}
}
