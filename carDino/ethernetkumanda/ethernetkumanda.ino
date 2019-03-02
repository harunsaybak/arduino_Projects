#include <SPI.h>
#include <Ethernet.h>

int pos = 0; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
byte ip[] = { 192, 168, 1, 20 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 1, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
Serial.begin(9600);
Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
 
  pinMode(4, OUTPUT);
  digitalWrite(4,HIGH);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
 

pinMode(A2,INPUT); pinMode(A3,INPUT);//x,y joyistik
}
int x,y;
int i;
void olc(){
    x=analogRead(A4);
  y=analogRead(A5);
  
  }
void loop() {
  
     EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
         //  Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>arduino ethernet </TITLE>");
           client.println("</HEAD>");
           client.println("<BODY bgcolor=""orange"">");
           client.println("<H1>uzaktan kontrol</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>uzaktan kumandali arabayi buradan kontrol edebilirsiniz...</H2>");
           client.println("<br />"); 
           client.println("<hr />");
           client.println("<br />"); 
           client.println("<hr />");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">illeri</a>");
           client.println("<a href=\"/?button1off\"\">geri</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<a href=\"/?button2on\"\">sola</a>");
           client.println("<a href=\"/?button2off\"\">saga</a><br />"); 
           client.println("<br />"); 
           client.println("<a href=\"/?button3on\"\">dur</a><br />");
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           
 i=1;
 
olc();


  
if (readString.indexOf("?button1on") >0)  {
  if(i==1) {
  Serial.print('b'); }
  i=0;
  olc();
  }
  i=1;

 
  if (readString.indexOf("?button1off") >0 )  {
  if(i==1) {
  Serial.print('e'); }
  i=0;
  olc();
  }
  i=1;


  if ( readString.indexOf("?button2on") >0 )   {
  if(i==1) {
  Serial.print('g'); }
  i=0;
  olc();
  }
  i=1;
  if ( readString.indexOf("?button2off") >0 )  {
  if(i==1) {
  Serial.print('h'); }
  i=0;
  olc();
  }
  i=1;
  if( readString.indexOf("?button3on") >0 ) {
    if(i==1) {
    Serial.print('q'); }
    i=0;
    olc();
    }

readString=""; }
}
    }
  }
}
