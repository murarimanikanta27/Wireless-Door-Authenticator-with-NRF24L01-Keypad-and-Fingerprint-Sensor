#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
Servo s;
int val;
int y;
int customKey;
RF24 radio(9, 10);
const byte address[6] = "12345";
void setup() {
  s.attach(6);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  lcd.init();
  lcd.backlight();
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Unlock door");
 s.write(0);
  // put your setup code here, to run once:


}


void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available())
  {
    Serial.println(val);
    Serial.println("connected");
    radio.read(&val, sizeof(val));
    int a=s.read();
    if(a==90)
    {
    Serial.print(a);
      lcd.clear();
      Serial.println("Door Unlocked");
      lcd.setCursor(0,0);
      lcd.print("Door Unlocked");
      lcd.setCursor(0,1);
      lcd.print("C button to lock");
      if(val==7){
        y=0;
         s.write(0);
         a=s.read();
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Door Locked");
         delay(1000);
      }
    }
    else
    {
    if(val==1)
    {
      lcd.clear();
      Serial.println("Too many unsuccessful fingerprint attempts ");
      lcd.setCursor(0,0);
     lcd.setCursor(0,0);
     lcd.print("Too many unsucce");
      lcd.setCursor(0,1);  
      lcd.print("-ssful attempts");
      delay(1500);
      lcd.clear();
      Serial.println("So plz try again with password");
      lcd.setCursor(0,0);
      lcd.print("So plz try again");
      lcd.setCursor(0,1);  
      lcd.print("with password");
      delay(1500);
      lcd.clear();
      unlock(1);
  }
  if(val==2)
    {
      lcd.clear();
      Serial.println("Found a print match!");
      lcd.setCursor(0,0);
      lcd.print("Found a print");
      lcd.setCursor(0,1);  
      lcd.print("match!");
      delay(1500);
      unlock(2);
      servo();
    }
  if(val==3)
    {
      lcd.clear();
      Serial.println("Did not found a match");
      lcd.setCursor(0,0);
      lcd.print("Finger did not");
      lcd.setCursor(0,1);  
      lcd.print("recognised!");
      delay(1500);
      unlock(1);
    }
  if(val==4)
    {
      Serial.println("correct Password");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Correct Password");
      unlock(2);
      servo();
    }
  if(val==5)
    {
      lcd.clear();
      Serial.println("wrong Password");
      lcd.setCursor(0,0);
      lcd.print("Wrong Password");
      delay(1500);
      unlock(1);
    }
    if(val==6)
    {
    Serial.println("Too many unsuccessful attempt's");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Too many unsucce");
    lcd.setCursor(0,1);  
    lcd.print("ssful attempts");
    delay(1500);
    lcd.clear();
    Serial.println("Try again after 60sec");
    lcd.setCursor(0,0);
    lcd.print("Try again after");
    lcd.setCursor(0,1);
    lcd.print("60 seconds");
    delay(60000);
    unlock(1);
    }
 
  }
}
  else
{
  //Serial.println("Disconnected");
}
}
void servo()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Door Unlocked");
  s.write(90);
 y=1;
}
void unlock(int a)
{
  if(a==1)
  {
    lcd.clear();
    Serial.println("unlock door");
    lcd.setCursor(0,0);
    lcd.print("Unlock door");
  }
  if(a==2){
    lcd.clear();
    Serial.println("Door Unlocked");
    lcd.setCursor(0,0);
    lcd.print("Door Unlocked");
  }
}




