#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

// Pins
const int buttonPin = 2;
const int buzzerPin = 9;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP); // Button → GND
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  if (!driver.init())
  {
    Serial.println("RF Init Failed");
    while (1);
  }

  Serial.println("Transmitter Ready");
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)
  {
    Serial.println("EMERGENCY SIGNAL SENT");

    //  Buzzer ON
    tone(buzzerPin, 1000);

    // Send signal multiple times (better reliability)
    const char *msg = "EMERGENCY";

    for (int i = 0; i < 3; i++)   // send 3 times
    {
      driver.send((uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();
      delay(100);
    }

    delay(300); // debounce delay
  }
  else
  {
    // Buzzer OFF
    noTone(buzzerPin);
  }
}
