#include <FastLED.h>
// C++ code
//

#define BUTTON1_PIN_RGB 2
#define BUTTON2_PIN_RGB 3
#define BUTTON3_PIN_RGB 4
#define BUTTON4_PIN_RGB 5
#define BUTTON5_PIN_RGB 6
#define BUTTON6_PIN_RGB 7

#define NUM_LEDS_RGB 6
#define LED_PIN_RGB 8

CRGB leds_rgb[NUM_LEDS_RGB];
String sequence_RGB = "999999";
String currentInput_RGB = "777777";

class LEDClass{
private:
  int selfIndex;
  int state = 0;
  
  public:
  int r;
  int g;
  int b;
  LEDClass(int index, int rIn, int bIn, int gIn){
    selfIndex = index;
    r = rIn;
    b = bIn;
    g = gIn;
  }

  void CycleSelf(){
    switch(state){
      case 0:
        r = 255;
        g = 0;
        b = 0;
        break;
      case 1:
        r = 0;
        g = 0;
        b = 255;
        break;
      case 2:
        r = 255;
        g = 0;
        b = 255;
        break;
      default:
        r = 255;
        g = 0;
        b = 0;
        break;
    }

    state++;

    if(state > 2){
      state = 0;
    }

    currentInput_RGB[selfIndex] = String(state)[0];
    leds_rgb[selfIndex] = CRGB(r, g, b);
    FastLED.show();
    Serial.println(currentInput_RGB);
    Serial.println(sequence_RGB);
  }

  void SetSolved(){
    r = 0;
    g = 255;
    b = 0;
    leds_rgb[selfIndex] = CRGB(r, g, b);
    FastLED.show();
  }
};

LEDClass RGB_LEDS[6] = {
  LEDClass(0, 255, 255, 255),
  LEDClass(1, 255, 255, 255),
  LEDClass(2, 255, 255, 255),
  LEDClass(3, 255, 255, 255),
  LEDClass(4, 255, 255, 255),
  LEDClass(5, 255, 255, 255),
};

void setup()
{
  pinMode(BUTTON1_PIN_RGB, INPUT);
  pinMode(BUTTON2_PIN_RGB, INPUT);
  pinMode(BUTTON3_PIN_RGB, INPUT);
  pinMode(BUTTON4_PIN_RGB, INPUT);
  pinMode(BUTTON5_PIN_RGB, INPUT);
  pinMode(BUTTON6_PIN_RGB, INPUT);

  FastLED.addLeds<WS2812B,LED_PIN_RGB,GRB>(leds_rgb,NUM_LEDS_RGB);
  
  for(int i = 0; i < 6; i++){
    leds_rgb[i] = CRGB(RGB_LEDS[i].r, RGB_LEDS[i].g, RGB_LEDS[i].b);
  }

  Serial.begin(9600);
}

bool pressedLast1;
bool pressedLast2;
bool pressedLast3;
bool pressedLast4;
bool pressedLast5;
bool pressedLast6;

bool RGBSolved;

void loop()
{
  ReadSerialData();

  if(sequence_RGB == currentInput_RGB && !RGBSolved){
    RGBSolved = true;
    Serial.println("$solved");
    for(int i = 0; i < 6; i++){
      RGB_LEDS[i].SetSolved();
    }
  }

  if(!RGBSolved){
    if(digitalRead(BUTTON1_PIN_RGB) == HIGH){
      if(!pressedLast1){
          pressedLast1 = true;
          RGB_LEDS[0].CycleSelf();
          delay(250);
      }
    } else{
      pressedLast1 = false;
    }

    if(digitalRead(BUTTON2_PIN_RGB) == HIGH){
      if(!pressedLast2){
          pressedLast2 = true;
          RGB_LEDS[1].CycleSelf();
          delay(250);
      }
    } else{
      pressedLast2 = false;
    }

    if(digitalRead(BUTTON3_PIN_RGB) == HIGH){
      if(!pressedLast3){
          pressedLast3 = true;
          RGB_LEDS[2].CycleSelf();
          delay(250);
      }
    } else{
      pressedLast3 = false;
    }

    if(digitalRead(BUTTON4_PIN_RGB) == HIGH){
      if(!pressedLast4){
          pressedLast4 = true;
          RGB_LEDS[3].CycleSelf();
          delay(250);
      }
    } else{
      pressedLast4 = false;
    }

    if(digitalRead(BUTTON5_PIN_RGB) == HIGH){
      if(!pressedLast5){
          pressedLast5 = true;
          RGB_LEDS[4].CycleSelf();
          delay(250);
      }
    } else{
      pressedLast5 = false;
    }

    if(digitalRead(BUTTON6_PIN_RGB) == HIGH){
      if(!pressedLast6){
          pressedLast6 = true;
          RGB_LEDS[5].CycleSelf();
          delay(250);
      }
    } else{
      pressedLast6 = false;
    }
  }
}

void ReadSerialData(){
  //reading data from unity for dynamic changes
  if (Serial.available() > 0) {
    String readData = Serial.readString();
    
    //simon says prefix: #
    if(readData.startsWith("#")){
      //sequence = readData.substring(1);
      //Serial.println(sequence);
    }
    
    //RGB prefix: $
    if(readData.startsWith("$")){
      //do stuff
      sequence_RGB = readData.substring(1);
      
      sequence_RGB.trim();
      Serial.println(sequence_RGB);
    }
    
    //RFID prefix: %
    if(readData.startsWith("%")){
      //do stuff
    }
  }
}