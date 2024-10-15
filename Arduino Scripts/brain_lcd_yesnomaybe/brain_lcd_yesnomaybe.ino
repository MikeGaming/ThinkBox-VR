#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

unsigned long last_time = 0;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
}

void loop()
{

  // Print a heartbeat
    if (millis() > last_time + 2000)
    {
      Serial.println("Arduino is alive!!");
      last_time = millis();
    }

  switch(Serial.read())
  {
    case 'y':
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("YES");
      break;
    case 'n':
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("NO");
      break;
    case 'm':
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("MAYBE");
      break;
  }
}

