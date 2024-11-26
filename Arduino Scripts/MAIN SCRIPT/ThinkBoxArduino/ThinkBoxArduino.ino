#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

unsigned long last_time = 0;

LiquidCrystal_I2C lcd(0x27,20,4);

int padIndex = 0;
String padText1[6] = {"SNAKE","BIRD","CAT","DOG","PLANE","BEACH"};
String padText2[6] = {"1","2","3","4","5","6"};
String padText3[6] = {"HELLO","BYE","THANKS","WOW","COOL","BRUH"};
String currentPadText[6] = {"TEXT1","TEXT2","TEXT3","TEXT4","TEXT5","TEXT6"};


void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Welcome to");
  lcd.setCursor(3,1);
  lcd.print("ThinkBox !");

  for(int i = 0; i < 6; i++)
  {
    currentPadText[i] = padText1[i];
  }
}

void loop()
{

  // Print a heartbeat
  if (millis() > last_time + 20000)
  {
    Serial.println("Arduino is alive!!");
    last_time = millis();
  }

  switch(padIndex)
  {
    case 0:
      for(int i = 0; i < 6; i++)
      {
        currentPadText[i] = padText1[i];
      }
      break;
    case 1:
      for(int i = 0; i < 6; i++)
      {
        currentPadText[i] = padText2[i];
      }
      break;
    case 2:
      for(int i = 0; i < 6; i++)
      {
        currentPadText[i] = padText3[i];
      }
      break;
  }

  switch(Serial.read())
  {
    case 'y':
      LCDPrint("YES");
      break;
    case 'n':
      LCDPrint("NO");
      break;
    case 'm':
      LCDPrint("IDK");
      break;
    case 't':
      padIndex++;
      if(padIndex >= 3) padIndex = 0;
      Serial.println(padIndex);
      break;
    case '1':
      LCDPrint(currentPadText[0]);
      break;
    case '2':
      LCDPrint(currentPadText[1]);
      break;
    case '3':
      LCDPrint(currentPadText[2]);
      break;
    case '4':
      LCDPrint(currentPadText[3]);
      break;
    case '5':
      LCDPrint(currentPadText[4]);
      break;
    case '6':
      LCDPrint(currentPadText[5]);
      break;
  }

}

void LCDPrint(String text) 
{
  lcd.clear();
  lcd.setCursor(8 - (int)(text.length() / 2),0);
  lcd.print(text);
}

