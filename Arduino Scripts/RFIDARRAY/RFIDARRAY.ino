/*
SNAKE 04 D0 B0 18 6F 61 80
04 CE 5D 75 8F 61 80
04 83 DF 18 6F 61 80
04 11 F2 18 6F 61 80
04 9E 60 72 8F 61 80
04 32 23 73 8F 61 80
*/

//RFID
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
// Init array that will store new NUID 
byte nuidPICC[4];
// Number of known default keys (hard-coded)
// NOTE: Synchronize the NR_KNOWN_KEYS define with the defaultKeys[] array
#define NR_KNOWN_KEYS 6
byte knownKeys[NR_KNOWN_KEYS][10] =  {
    {0x04, 0xD0, 0xB0, 0x18, 0x6F, 0x61, 0x80}, // SNAKE
    {0x04, 0xD0, 0xB0, 0x18, 0x6F, 0x61, 0x80}, //
    {0x04, 0xD0, 0xB0, 0x18, 0x6F, 0x61, 0x80}, //
    {0x04, 0xD0, 0xB0, 0x18, 0x6F, 0x61, 0x80}, //
    {0x04, 0xD0, 0xB0, 0x18, 0x6F, 0x61, 0x80}, //
    {0x04, 0xD0, 0xB0, 0x18, 0x6F, 0x61, 0x80}, //
};
//RFID

//LED ARRAY
#include <FastLED.h>
#define NUM_LEDS 64
#define DATA_PIN 12
CRGB leds[NUM_LEDS];
int Snake [8][8][3]{{
  {0, 0, 0}, {0, 135, 81}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 135, 81}, {0, 0, 0}, {0, 0, 0}}, 
  {{0, 135, 81}, {126, 37, 83}, {0, 228, 54}, {126, 37, 83}, {0, 228, 54}, {0, 228, 54}, {0, 135, 81}, {0, 0, 0}}, 
  {{0, 135, 81}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 0, 0}, {0, 228, 54}, {0, 228, 54}, {0, 0, 0}}, 
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 228, 54}, {0, 228, 54}, {0, 135, 81}, {0, 0, 0}}, 
  {{0, 135, 81}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 135, 81}, {0, 0, 0}, {0, 228, 54}}, 
  {{0, 228, 54}, {0, 228, 54}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 228, 54}}, 
  {{0, 135, 81}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 135, 81}}, 
  {{0, 0, 0}, {0, 135, 81}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 228, 54}, {0, 135, 81}, {0, 0, 0}}
};
//LED ARRAY

void setup() { 
  //RFID
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  //RFID

  //LED ARRAY
  FastLED.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  FastLED.setBrightness(150);
  //LED ARRAY
 
}
 
void loop() {
  
  //RFID
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) return;
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial()) return;
  for (byte i = 0; i < 4; i++)
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  //RFID

  //LED ARRAY CHANGING
  if(rfid.uid.uidByte == knownKeys[0])
  {
    ChangeSymbol(Snake);
  }
  else if(rfid.uid.uidByte == knownKeys[1])
  {
    ChangeSymbol(Snake);
  }
  else if(rfid.uid.uidByte == knownKeys[2])
  {
    ChangeSymbol(Snake);
  }
  else if(rfid.uid.uidByte == knownKeys[3])
  {
    ChangeSymbol(Snake);
  }
  else if(rfid.uid.uidByte == knownKeys[4])
  {
    ChangeSymbol(Snake);
  }
  else if(rfid.uid.uidByte == knownKeys[5])
  {
    ChangeSymbol(Snake);
  }
  //LED ARRAY CHANGING
}



void printHex(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


void ChangeSymbol(int symbol[8][8][3])
{
  for (int j=0;j<8;j++)
  {
    for (int i=0;i<8;i++)
    {
      if (!(j&1)and symbol[i][j]==0) leds[j*8+i]=CRGB(0,0,0);
      if (!(j&1)and symbol[i][j]!=0) leds[j*8+i]=CRGB(symbol[i][j]);
      if (j&1 and  symbol[i][j]==0 ) leds[j*8+7-i]=CRGB(0,0,0);
      if (j&1 and  symbol[i][j]!=0 ) leds[j*8+7-i]=CRGB(symbol[i][j]);
      delay(1);
      FastLED.show();
    }
  }
}