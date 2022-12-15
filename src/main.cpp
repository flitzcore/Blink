#include <Arduino.h>

const int LEDBuiltIn = PC13;
const int potPin = PA3;
const int LEDEksternalPin = PA1;
const int key = PA0;
float ledFade = 0;
unsigned long lastFadeTime;
unsigned long lastPrintTime = 0;
const long fadeTime = 20;
float dimSpeed = 10;
int buttonState;
bool fadeup;
int potValue;
double vPot;
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LEDBuiltIn, OUTPUT);
  // Untuk potensio
  pinMode(potPin, INPUT);
  // led eksternal
  pinMode(LEDEksternalPin, OUTPUT);
  pinMode(key, INPUT_PULLUP);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
  buttonState = digitalRead(key);
  if (buttonState == HIGH)
    ledFade = 0;
  else
  {
    if (millis() - lastFadeTime > fadeTime)
    {
      if (fadeup)
      {
        analogWrite(LEDEksternalPin, ledFade);
        ledFade += dimSpeed;
        if (ledFade >= 255)
        {
          ledFade = 255;
          fadeup = false;
        }
      }
      else
      {
        analogWrite(LEDEksternalPin, ledFade);
        ledFade -= dimSpeed;
        if (ledFade <= 0)
        {
          ledFade = 0;
          fadeup = true;
        }
      }
      lastFadeTime = millis();
    }
  }

  potValue = analogRead(potPin);
  vPot = (double)(potValue / 1023.00) * 5.00;
  if (millis() - lastPrintTime > 5000)
  {
    Serial.print("Tegangan Analog: ");
    Serial.print(vPot, 2);
    Serial.println(" volt");
    lastPrintTime = millis();
  }

  analogWrite(LEDEksternalPin, ledFade);
  if (vPot < 2)
    digitalWrite(LEDBuiltIn, HIGH);
  else
    digitalWrite(LEDBuiltIn, LOW);
}