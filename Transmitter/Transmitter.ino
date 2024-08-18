#include <Adafruit_Fingerprint.h>
#include <Keypad.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif
char w[60]="123456";
char q[60];
const byte ROWS = 4;
const byte COLS = 4;
char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','B'}
  };
  int i=0;
  int j=0;
  char z[1];
  char customKey ;
int password_length=6;
int val;
byte rowPins[ROWS] =  {7,6,5,4};
byte colPins[COLS] = {A0,A1,A2,A3};
Keypad customKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS);
int count=0;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
RF24 radio(9, 8);  
const byte address[6] = "12345";
void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor");
         }
  }
void loop()                     // run over and over again
{
  keyboardinput();


  uint8_t p = finger.getImage();
  if(count<=5)
  {
  if(keyboardinput());
   if(p==FINGERPRINT_OK)
   {
    //Serial.println("Image taken");
    searchfinger();
   }
  }
  else if(p==FINGERPRINT_OK && count>=6)
  {
    val=1;
    //radio.write(&val, sizeof(val));
   //Serial.println("Too many unsuccessful fingerprint attempts ");
   //Serial.println("So plz enter the password");
  }
  if(count==10)
  {
    val=6;
    count=0;
    //radio.write(&val, sizeof(val));
    Serial.println("Too many unsuccessful attempt's");
    Serial.println("Try again after 60sec");
    delay(10000);
  }
  Serial.println(val);
  radio.write(&val, sizeof(val));
  val=0;
  customKey=0;
}
uint8_t searchfinger()
{
   uint8_t p=finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
    //radio.write(&val, sizeof(val));
      //Serial.println("Image taken");
      break;
    }
     p = finger.image2Tz();
    switch (p) {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
  }
      p=finger.fingerSearch();
      if (p == FINGERPRINT_OK) {
        count=0;
        val=2;
        j=2;
       
       
    //radio.write(&val, sizeof(val));
    Serial.println("Found a print match!");
 


  }
    else if (p == FINGERPRINT_NOTFOUND) {
    count++;
     val=3;
    //radio.write(&val, sizeof(val));
    Serial.println("Did not found a match");
   
  }  
  }


char keyboardinput()
{
char customKey = customKeypad.getKey();


if (customKey == 'C'&&(j==1||j==2)) {
  j=0;
  val=7;
    Serial.println("door locked"); // or perform any other action
  }
else{
if(customKey)
{
  q[i]=customKey;
  i++;
  Serial.println(customKey);
  delay(100);


}


if(i==password_length)
{
  int s=strcmp(q,w);
  if (s==0)
  {j=1;
    count=0;
     val=4;
  //  radio.write(&val, sizeof(val));
    Serial.println("correct Password");
    i=0;
   
  }
   else
  { count++;
    val=5;
    Serial.println("wrong Password");
    i=0;
  }
}


}
}


