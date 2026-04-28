#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Lane A
int A_red = 3;
int A_yellow = 4;
int A_green = 5;

// Lane B
int B_red = 6;
int B_yellow = 7;
int B_green = 8;

// Emergency Button
int buttonPin = 2;

void setup()
{
  pinMode(A_red, OUTPUT);
  pinMode(A_yellow, OUTPUT);
  pinMode(A_green, OUTPUT);

  pinMode(B_red, OUTPUT);
  pinMode(B_yellow, OUTPUT);
  pinMode(B_green, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.print("Traffic System");
  delay(2000);
  lcd.clear();
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    ambulanceMode();  //  Emergency
  }
  else
  {
    normalCycle();    //  Normal
  }
}

// Emergency Mode
void ambulanceMode()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EMERGENCY VEHICLE");
  lcd.setCursor(0,1);
  lcd.print("GIVE WAY !!!");

  // Lane A GREEN
  digitalWrite(A_red, LOW);
  digitalWrite(A_yellow, LOW);
  digitalWrite(A_green, HIGH);

  // Lane B RED
  digitalWrite(B_red, HIGH);
  digitalWrite(B_yellow, LOW);
  digitalWrite(B_green, LOW);

  delay(500);
}

// 🚦 Normal Traffic Cycle
void normalCycle()
{
  // Lane A GREEN
  lcd.clear();
  lcd.print("Lane A GO");

  digitalWrite(A_green, HIGH);
  digitalWrite(A_red, LOW);
  digitalWrite(A_yellow, LOW);

  digitalWrite(B_red, HIGH);
  digitalWrite(B_green, LOW);
  digitalWrite(B_yellow, LOW);

  delay(4000);
  if (digitalRead(buttonPin) == LOW) return;

  // Lane A YELLOW
  lcd.clear();
  lcd.print("Lane A WAIT");

  digitalWrite(A_green, LOW);
  digitalWrite(A_yellow, HIGH);

  delay(2000);
  if (digitalRead(buttonPin) == LOW) return;

  // Lane B GREEN
  lcd.clear();
  lcd.print("Lane B GO");

  digitalWrite(A_red, HIGH);
  digitalWrite(A_yellow, LOW);

  digitalWrite(B_red, LOW);
  digitalWrite(B_green, HIGH);

  delay(4000);
  if (digitalRead(buttonPin) == LOW) return;

  // Lane B YELLOW
  lcd.clear();
  lcd.print("Lane B WAIT");

  digitalWrite(B_green, LOW);
  digitalWrite(B_yellow, HIGH);

  delay(2000);
}
