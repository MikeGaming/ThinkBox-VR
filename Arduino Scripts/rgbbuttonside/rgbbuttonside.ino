// C++ code
//

#define BUTTON_PIN 2
#define BUTTON_PIN 3
#define BUTTON_PIN 4
#define BUTTON_PIN 5
#define BUTTON_PIN 6
#define BUTTON_PIN 7
#define LED_PIN_RGB 8
#

#define

const int RED = 0;
const int BLUE = 1;
const int GREEN = 2;

int buttonState;
bool pressedLast = false;

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(BUTTON_PIN) == HIGH){
    if(!pressedLast){
          pressedLast = true;
        ChangeColor();
    }
  } else{
    pressedLast = false;
  }
  delay(100);
}

void ChangeColor()
{
  ResetLED();
  switch(buttonState){
    case RED:
      digitalWrite(RED_PIN, HIGH);
        Serial.println("red");
      break;
    case BLUE:
      digitalWrite(BLUE_PIN, HIGH);
        Serial.println("blue");
      break;
    case GREEN:
      digitalWrite(GREEN_PIN, HIGH);
        Serial.println("green");
      break;
      
    //should never hit default
    default:
      break;
  }
  
  buttonState = buttonState + 1;
  buttonState = RollOver(buttonState, RED, GREEN);
}

void ResetLED()
{
  digitalWrite(RED_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

int RollOver(int input, int min, int max){
  if(input > max){
    return min;
  }else{
    return input;
  }
}