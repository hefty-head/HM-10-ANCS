#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX  
 
String currentCom = "";
char NotifType;
char NotifCat;
char CatCount[2];
char NotifUID[4];
// Connect HM10      Arduino Uno
//     Pin 1/TXD          Pin 7
//     Pin 2/RXD          Pin 8

String inputString = "";
boolean stringComplete = false;

void setup() {  
  Serial.begin(9600);
  // If the baudrate of the HM-10 module has been updated,
  // you may need to change 9600 by another value
  // Once you have found the correct baudrate,
  // you can update it using AT+BAUDx command 
  // e.g. AT+BAUD0 for 9600 bauds
  mySerial.begin(9600);
  inputString.reserve(200);

}




void printType(char type)
{
  switch (type)
  {
    case '0':
      Serial.print("Notif Added\n");
      break;
    case '1':
      Serial.print("Notif Modded\n");
      break;
    case '2':
      Serial.print("Notif Removed\n");
      break;
  }
}

void printID(char ID)
{
  switch (ID)
  {
    case '0':
      Serial.print("Other\n");
      break;
    case '1':
      Serial.print("Incoming Call\n");
      break;
    case '2':
      Serial.print("Missed Call\n");
      break;
    case '3':
      Serial.print("Voicemail\n");
      break;
    case '4':
      Serial.print("Social\n");
      break;
    case '5':
      Serial.print("Schedule\n");
      break;
    case '6':
      Serial.print("Email\n");
      break;
    case '7':
      Serial.print("News\n");
      break;
    case '8':
      Serial.print("Health\n");
      break;
    case '9':
      Serial.print("Buss\n");
      break;
    case 'A':
      Serial.print("Location\n");
      break;
    case 'B':
      Serial.print("Entertainment\n");
      break;
  }
}

void getData(int ID)
{
  if(mySerial.available())
  {
    String sendS = "AT+ANCS";
    sendS += ID;
    sendS += 3;
    sendS += 100;
    Serial.print(sendS);
    //mySerial.print(sendS);
    
  }
}

void loop() {  
  char c;
  //serialEvent();
  char d;
  if (Serial.available()) {
    c = Serial.read();
   
    mySerial.print(c);
  }
 // Serial.print(mySerial.available());
  if (mySerial.available()) {
    char ANCS8Buffer[16];

    //Reads 16 bytes into a buffer, the total of OK+ combined with the ANCS8 request
    c = mySerial.readBytes(ANCS8Buffer, 16);
        Serial.print("\n");
    //This section of code acts on the buffer to draw out the easy information about the notification, the next block will use this info to learn more
    NotifType = ANCS8Buffer[8];
    printType(NotifType);

    NotifCat = ANCS8Buffer[9];
    printID(NotifCat);

    CatCount[0] = ANCS8Buffer[10];
    CatCount[1] = ANCS8Buffer[11];

    NotifUID[0] = ANCS8Buffer[12];
    NotifUID[1] = ANCS8Buffer[13];
    NotifUID[2] = ANCS8Buffer[14];
    NotifUID[3] = ANCS8Buffer[15];
    
    Serial.print(ANCS8Buffer);
    //This section of code acts on the buffer to draw out the easy information about the notification, the next block will use this info to learn more
      //  Serial.print("\n");

/*    char NARequest[14];
    NARequest[0] = 'A';
    NARequest[1] = 'T';
    NARequest[2] = '+';
    NARequest[3] = 'A';
    NARequest[4] = 'N';
    NARequest[5] = 'C'; 
    NARequest[6] = 'S';
       
    NARequest[7] = NotifUID[0];
    NARequest[8] = NotifUID[1];
    NARequest[9] = NotifUID[2];
    NARequest[10] = NotifUID[3];

    NARequest[11] = '3';
  
    NARequest[12] = 'F';
    NARequest[13] = 'F';

   
    //Serial.print("");
    //mySerial.write(NARequest, 14);*/
    
  
}

}
