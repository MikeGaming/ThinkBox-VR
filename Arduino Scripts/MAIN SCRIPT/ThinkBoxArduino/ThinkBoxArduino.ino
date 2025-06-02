//RFIDARRAY
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53
#define RST_PIN 49
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
// Init array that will store new NUID 
byte nuidPICC[4];
// Number of known default keys (hard-coded)
// NOTE: Synchronize the NR_KNOWN_KEYS define with the defaultKeys[] array
#define NR_KNOWN_KEYS 6
byte knownKeys[NR_KNOWN_KEYS][10] =  {
    {0x04, 0xD0, 0xB0, 0x18, 0x6F, 0x61, 0x80}, // SNAKE
    {0x04, 0xCE, 0x5D, 0x75, 0x8F, 0x61, 0x80}, // TURTLE
    {0x04, 0x83, 0xDF, 0x18, 0x6F, 0x61, 0x80}, // SNAIL
    {0x04, 0x11, 0xF2, 0x18, 0x6F, 0x61, 0x80}, // FOX
    {0x04, 0x9E, 0x60, 0x72, 0x8F, 0x61, 0x80}, // CHICKEN
    {0x04, 0x32, 0x23, 0x73, 0x8F, 0x61, 0x80}, // CAT
};
int currentKey;
//RFID

#define BUTTON_PIN_ARRAY 22

//LED ARRAY
#include <FastLED.h>
#define NUM_LEDS_ARRAY 64
#define DATA_PIN_ARRAY 3
CRGB leds[NUM_LEDS_ARRAY];
int symbols [6][64][3] = {
//SNAKE  
{{0, 0, 0}, {106, 190, 48}, {0, 0, 0}, {106, 190, 48}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{106, 190, 48}, {95, 12, 12}, {106, 190, 48}, {95, 12, 12}, {106, 190, 48}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{106, 190, 48}, {106, 190, 48}, {106, 190, 48}, {106, 190, 48}, {106, 190, 48}, {0, 0, 0}, {106, 190, 48}, {106, 190, 48}, 
{0, 0, 0}, {255, 255, 255}, {172, 50, 50}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {106, 190, 48}, 
{0, 0, 0}, {106, 190, 48}, {153, 229, 80}, {106, 190, 48}, {0, 0, 0}, {0, 0, 0}, {106, 190, 48}, {106, 190, 48}, 
{0, 0, 0}, {106, 190, 48}, {153, 229, 80}, {106, 190, 48}, {0, 0, 0}, {0, 0, 0}, {106, 190, 48}, {153, 229, 80}, 
{0, 0, 0}, {106, 190, 48}, {153, 229, 80}, {106, 190, 48}, {106, 190, 48}, {106, 190, 48}, {106, 190, 48}, {153, 229, 80}, 
{0, 0, 0}, {106, 190, 48}, {153, 229, 80}, {153, 229, 80}, {153, 229, 80}, {153, 229, 80}, {153, 229, 80}, {153, 229, 80}}, 
//TURTLE
{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {17, 109, 71}, {55, 148, 110}, {17, 109, 71}, {0, 0, 0}, {153, 229, 80}, {153, 229, 80}, {0, 0, 0}, 
{17, 109, 71}, {55, 148, 110}, {17, 109, 71}, {55, 148, 110}, {55, 148, 110}, {153, 229, 80}, {102, 57, 49}, {153, 229, 80}, 
{17, 109, 71}, {17, 109, 71}, {55, 148, 110}, {17, 109, 71}, {238, 195, 154}, {153, 229, 80}, {153, 229, 80}, {153, 229, 80}, 
{198, 150, 104}, {238, 195, 154}, {198, 150, 104}, {238, 195, 154}, {198, 150, 104}, {238, 195, 154}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {153, 229, 80}, {153, 229, 80}, {0, 0, 0}, {153, 229, 80}, {153, 229, 80}, {0, 0, 0}, {0, 0, 0}},
//SNAIL
{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{217, 160, 102}, {0, 0, 0}, {217, 160, 102}, {0, 0, 0}, {143, 86, 59}, {143, 86, 59}, {143, 86, 59}, {0, 0, 0}, 
{238, 195, 154}, {0, 0, 0}, {238, 195, 154}, {143, 86, 59}, {143, 86, 59}, {102, 57, 49}, {143, 86, 59}, {143, 86, 59}, 
{238, 195, 154}, {238, 195, 154}, {238, 195, 154}, {143, 86, 59}, {102, 57, 49}, {143, 86, 59}, {143, 86, 59}, {102, 57, 49}, 
{0, 0, 0}, {238, 195, 154}, {238, 195, 154}, {143, 86, 59}, {143, 86, 59}, {102, 57, 49}, {102, 57, 49}, {73, 28, 20}, 
{0, 0, 0}, {217, 160, 102}, {238, 195, 154}, {238, 195, 154}, {73, 28, 20}, {73, 28, 20}, {73, 28, 20}, {0, 0, 0}, 
{0, 0, 0}, {217, 160, 102}, {217, 160, 102}, {217, 160, 102}, {217, 160, 102}, {217, 160, 102}, {217, 160, 102}, {217, 160, 102}},
//FOX
{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{255, 255, 255}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {223, 113, 38}, {0, 0, 0}, {223, 113, 38}, {0, 0, 0}, 
{255, 255, 255}, {223, 113, 38}, {0, 0, 0}, {0, 0, 0}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, 
{223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {0, 0, 0}, {223, 113, 38}, {74, 33, 5}, {223, 113, 38}, {74, 33, 5}, 
{223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, 
{0, 0, 0}, {0, 0, 0}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {0, 0, 0}, 
{0, 0, 0}, {0, 0, 0}, {202, 96, 25}, {223, 113, 38}, {202, 96, 25}, {223, 113, 38}, {202, 96, 25}, {0, 0, 0}, 
{0, 0, 0}, {0, 0, 0}, {115, 53, 10}, {0, 0, 0}, {115, 53, 10}, {0, 0, 0}, {115, 53, 10}, {0, 0, 0}},
//CHICKEN
{{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{251, 242, 54}, {251, 242, 54}, {255, 255, 255}, {0, 0, 185}, {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {255, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, 
{255, 0, 0}, {255, 255, 255}, {255, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {201, 246, 255}, 
{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {201, 246, 255}, {201, 246, 255}, {201, 246, 255}, {255, 255, 255}, 
{0, 0, 0}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, {255, 255, 255}, 
{0, 0, 0}, {0, 0, 0}, {251, 242, 54}, {251, 242, 54}, {0, 0, 0}, {251, 242, 54}, {251, 242, 54}, {0, 0, 0}},
//CAT
{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {223, 113, 38}, {0, 0, 0}, {223, 113, 38}, {0, 0, 0}, {0, 0, 0}, {223, 113, 38}, {244, 225, 207}, 
{223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {223, 113, 38}, {0, 0, 0}, {0, 0, 0}, {210, 100, 26}, {0, 0, 0}, 
{55, 148, 110}, {223, 113, 38}, {55, 148, 110}, {223, 113, 38}, {0, 0, 0}, {0, 0, 0}, {210, 100, 26}, {0, 0, 0}, 
{223, 113, 38}, {255, 179, 231}, {223, 113, 38}, {223, 113, 38}, {210, 100, 26}, {210, 100, 26}, {210, 100, 26}, {0, 0, 0}, 
{0, 0, 0}, {210, 100, 26}, {210, 100, 26}, {210, 100, 26}, {210, 100, 26}, {210, 100, 26}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {210, 100, 26}, {210, 100, 26}, {210, 100, 26}, {210, 100, 26}, {210, 100, 26}, {0, 0, 0}, {0, 0, 0}, 
{0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {255, 255, 255}, {0, 0, 0}, {210, 100, 26}, {0, 0, 0}, {0, 0, 0}}
};
//LED ARRAY

bool readyToWin;
//RFIDARRAY 



//RGB BUTTONS
#define BUTTON1_PIN_RGB A0
#define BUTTON2_PIN_RGB A1
#define BUTTON3_PIN_RGB A2
#define BUTTON4_PIN_RGB A3
#define BUTTON5_PIN_RGB A4
#define BUTTON6_PIN_RGB A5

#define NUM_LEDS_RGB 6
#define LED_PIN_RGB 48

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
    Serial.println("$" + currentInput_RGB);
    //Serial.println(sequence_RGB);

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

bool pressedLast1;
bool pressedLast2;
bool pressedLast3;
bool pressedLast4;
bool pressedLast5;
bool pressedLast6;

bool RGBSolved;
//RGB BUTTONS




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








#include <Wire.h>
#include <LiquidCrystal_I2C.h>

unsigned long last_time = 0;

LiquidCrystal_I2C lcd(0x27,20,4);

int padIndex = 0;
String padText1[6] = {"SNAKE","TURTLE","SNAIL","FOX","CHICKEN","CAT"};
String padText2[6] = {"TRIANGLE","CIRCLE","SQUARE","DIAMOND","",""};
String padText3[6] = {"RED","BLUE","PURPLE","","",""};
String currentPadText[6] = {"TEXT1","TEXT2","TEXT3","TEXT4","TEXT5","TEXT6"};


void setup()
{

  FastLED.addLeds<WS2812B,LED_PIN_SIMON,GRB>(leds_simon,NUM_LEDS_SIMON);
  
  pinMode(_button1Pin, INPUT);
  pinMode(_button2Pin, INPUT);
  pinMode(_button3Pin, INPUT);
  pinMode(_button4Pin, INPUT);


  //RGB BUTTON
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
  //RGB BUTTON

  //RFID
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  //RFID

  pinMode(BUTTON_PIN_ARRAY, INPUT);

  //LED ARRAY
  FastLED.addLeds<WS2812B,DATA_PIN_ARRAY,GRB>(leds,NUM_LEDS_ARRAY).setRgbw(RgbwDefault());
  FastLED.setBrightness(64);

  randomSeed(analogRead(0));
  currentKey = random(0, 6);
  ChangeSymbol(symbols[currentKey]);

  FastLED.show();
  //LED ARRAY











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
bool solved_rfid;
void loop()
{
  ReadSerialData();


  //RGB BUTTON
if(sequence_RGB == currentInput_RGB && !RGBSolved){
    RGBSolved = true;
    Serial.println("$s");
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
  //RGB BUTTON




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

if (!solved_rfid)
  {
    if (readyToWin && digitalRead(BUTTON_PIN_ARRAY) == HIGH)
    {
      Serial.println("#s");
      readyToWin = false;
      solved_rfid = true;
      for (int i=0;i<NUM_LEDS_ARRAY;i++)
      {
        leds[i] = CRGB(0, 255, 0);
      }
      FastLED.show();
    }

    //RFID
    // Look for new cards
    if ( ! rfid.PICC_IsNewCardPresent()) return;
    // Verify if the NUID has been readed
    if ( ! rfid.PICC_ReadCardSerial()) return;
    for (byte i = 0; i < 4; i++)
    {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
    //printHex(rfid.uid.uidByte, rfid.uid.size);
    //Serial.println();
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    //RFID

    Serial.println("%" + rfid.uid.uidByte[1]);
    if(rfid.uid.uidByte[1] == knownKeys[currentKey][1])
    {
      readyToWin = true;
      Serial.println("ready to win");
    }

    if(rfid.uid.uidByte[1] == knownKeys[0][1])
    {
      Serial.println("%Snake");
    }
    else if(rfid.uid.uidByte[1] == knownKeys[1][1])
    {
      Serial.println("%Turtle");
    }
    else if(rfid.uid.uidByte[1] == knownKeys[2][1])
    {
      Serial.println("%Snail");
    }
    else if(rfid.uid.uidByte[1] == knownKeys[3][1])
    {
      Serial.println("%Fox");
    }
    else if(rfid.uid.uidByte[1] == knownKeys[4][1])
    {
      Serial.println("%Chicken");
    }
    else if(rfid.uid.uidByte[1] == knownKeys[5][1])
    {
      Serial.println("%Cat");
    }

    delay(500);
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
      sequence_RGB = readData.substring(1, 7);
      sequence_RGB.trim();
      Serial.println(sequence_RGB);
    }
    
    //RFID prefix: %
    if(readData.startsWith("%")){
      //do stuff
    }

    if(readData.startsWith("*"))
    {
      if(readData.substring(1, 2) == "y")
      {
        LCDPrint("YES");
        Serial.println(readData.substring(1, 1));
      }
      else if(readData.substring(1, 2) == "m")
      {
        LCDPrint("IDK");
      }
      else if(readData.substring(1, 2) == "n")
      {
        LCDPrint("NO");
      }
      else if(readData.substring(1, 2) == "t")
      {
        padIndex++;
        if(padIndex > 2) padIndex = 0;
        Serial.println(padIndex);
      }
      else if(readData.substring(1, 2) == "1")
      {
        LCDPrint(currentPadText[0]);
      }
      else if(readData.substring(1, 2) == "2")
      {
        LCDPrint(currentPadText[1]);
      }
      else if(readData.substring(1, 2) == "3")
      {
        LCDPrint(currentPadText[2]);
      }
      else if(readData.substring(1, 2) == "4")
      {
        LCDPrint(currentPadText[3]);
      }
      else if(readData.substring(1, 2) == "5")
      {
        LCDPrint(currentPadText[4]);
      }
      else if(readData.substring(1, 2) == "6")
      {
        LCDPrint(currentPadText[5]);
      }
      
    }

    Serial.flush();
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

void LCDPrint(String text) 
{
  lcd.clear();
  lcd.setCursor(8 - (int)(text.length() / 2),0);
  lcd.print(text);
}

void ChangeSymbol(int symbol[NUM_LEDS_ARRAY][3])
{
  for (int i=0;i<NUM_LEDS_ARRAY;i++)
  {
    leds[i]=CRGB(symbol[i][0], symbol[i][1], symbol[i][2]);
  }
}