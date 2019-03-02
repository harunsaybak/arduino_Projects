#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

String lastRfid = "";
String kart1 = "";
String kart2 = "";

MFRC522::MIFARE_Key key;

void setup(){ 
  
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  
//  Serial.println("RFID KART OKUMA UYGULAMASI");
 // Serial.println("————————–"); 
 // Serial.println(); 
  //EEPROM’dan kart bilgisini oku 
 // readEEPROM();
  }

 bool flag =true;
 String rfid = " ";
 String rfid2 = " ";
  void loop(){
    //yeni kart okununmadıkça devam etme 
  
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return; 
      } 
    
      if ( ! mfrc522.PICC_ReadCardSerial()) { 
        return; 
        }
        //kartın UID’sini oku, rfid isimli string’e kaydet 
         

       //   mfrc522.PICC_IsNewCardPresent();
      //    mfrc522.PICC_ReadCardSerial();
        rfid = " ";
        
        for (byte i = 0; i < mfrc522.uid.size; i++) {
          //rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "; 
          rfid += String(mfrc522.uid.uidByte[i], HEX); 
          }
          
          //string’in boyutunu ayarla ve tamamını büyük harfe çevir
          rfid.trim(); 
          rfid.toUpperCase();
       /*    Serial.print("rfid");
            Serial.println(rfid);
           Serial.print("Lasrfid");
            Serial.println(lastRfid);
             */
       //   if (rfid != lastRfid && rfid != " "){ 
          //Serial.println("girdi");
       //   return; 
    //         rfid2 =rfid;
           //  Serial.println("girdi");          
   //       }

         // if(rfid != lastRfid){
       
            
         // }
          lastRfid = rfid; 
         // Serial.print("Kart 1: ");
         // Serial.println(kart1); 
         // Serial.print("Kart 2: ");
         // Serial.println(kart2); 
         // Serial.print("Okunan: ");

   /*     if( Serial.available()>0){
           
         String aa = Serial.readString();
         if(aa = "ver"){
          Serial.println(rfid);
         // Serial.print("G");
         } 
         //Serial.println(); //1 nolu kart okunduysa LED’i yak, 2 nolu kart okunduysa LED’i söndür 
        } */ 
  //             if( Serial.available()>0){
           
 //        String aa = Serial.readString();
//         if(aa = "flg"){
           Serial.println(rfid);
         // Serial.print("G");
//         } 
 //             }
              delay(200);
              }
              void readEEPROM(){
                //EEPROM’dan ilk kartın UID’sini oku (ilk 4 byte) 
                
                /*for (int i = 0 ; i < 7 ; i++) {
                  kart1 += EEPROM.read(i) < 0x10 ? "0" : " "; 
                  kart1 += String(EEPROM.read(i), HEX); 
                 
                  } //EEPROM’dan ikinci kartın UID’sini oku 
                  
                  for (int i = 7 ; i < 14 ; i++) {
                    kart2 += EEPROM.read(i) < 0x10 ? "0" : " "; 
                    kart2 += String(EEPROM.read(i), HEX); } 
                    //Okunan stringleri düzenle
                    kart1.trim(); 
                    kart1.toUpperCase(); 
                    kart2.trim(); 
                    kart2.toUpperCase();
                    */
                  }
