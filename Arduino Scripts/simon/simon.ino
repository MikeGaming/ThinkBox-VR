#include <FastLED.h>

// C++ code
//

#define NUM_LEDS_SIMON 4
#define LED_PIN_SIMON 2
CRGB leds_simon[NUM_LEDS_SIMON];

#define _button1Pin 7 
#define _button2Pin 6
#define _button3Pin 5
#define _button4Pin 4

bool simonSolved = false;
//sequence must be defined here.
//it is impossible for the sequence to be solved with values above 4
String sequence_simon = "5555";
String currentInput_simon = "";

void setup()
{
  FastLED.addLeds<WS2812B,LED_PIN_SIMON,GRB>(leds_simon,NUM_LEDS_SIMON);
  
  pinMode(_button1Pin, INPUT);
  pinMode(_button2Pin, INPUT);
  pinMode(_button3Pin, INPUT);
  pinMode(_button4Pin, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  ReadSerialData();
  
  if(sequence_simon.length() == currentInput_simon.length() && !simonSolved){
    Serial.println("Alert6");
    
    if(sequence_simon == currentInput_simon){
      simonSolved = true;
      Serial.println("#s");
      leds_simon[0] = CRGB(0, 255, 0);
      leds_simon[1] = CRGB(0, 255, 0);
      leds_simon[2] = CRGB(0, 255, 0);
      leds_simon[3] = CRGB(0, 255, 0);
      FastLED.show();
    }else{
      ResetSimon();
    }
  }
  
  if(!simonSolved){
    if(digitalRead(_button1Pin) == HIGH){
      currentInput_simon += '1';
      //replace next with LED array change
      leds_simon[1]=CRGB(255, 255, 255);
      FastLED.show();
      Serial.println("alert1");
      delay(250);
    }

    if(digitalRead(_button2Pin) == HIGH){
      currentInput_simon += '2';
      //replace next with LED array change
      leds_simon[0]=CRGB(255, 255, 255);
      FastLED.show();
      Serial.println("alert2");
      delay(250);
    }

    if(digitalRead(_button3Pin) == HIGH){
      currentInput_simon += '3';
      //replace next with LED array change
      leds_simon[3]=CRGB(255, 255, 255);
      FastLED.show();
      Serial.println("alert3");
      delay(250);
    }

    if(digitalRead(_button4Pin) == HIGH){
      currentInput_simon += '4';
      //replace next with LED array change
      leds_simon[2]=CRGB(255, 255, 255);
      FastLED.show();
      Serial.println("alert4");
      delay(250);
    }
  }  
}

String readData = "";

void ReadSerialData(){
  //reading data from unity for dynamic changes
  if (Serial.available() > 0) {
    readData = Serial.readString();
    
    //simon says prefix: #
    if(readData.startsWith("#")){
      sequence_simon = readData.substring(1, 5);
      sequence_simon.trim();
      Serial.println(sequence_simon);
    }
    
    //RGB prefix: $
    if(readData.startsWith("$")){
      //do stuff
    }
    
    //RFID prefix: %
    if(readData.startsWith("%")){
      //do stuff
    }
  }
}

void ResetSimon(){
  //replace next with LED array change
  leds_simon[0]=CRGB(0);
  leds_simon[1]=CRGB(0);
  leds_simon[2]=CRGB(0);
  leds_simon[3]=CRGB(0);
  FastLED.show();

  currentInput_simon = "";
}