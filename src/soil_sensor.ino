#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*
//Set the pins on the I2C chip used for LCD connections
//ADDR,EN,R/W,RS,D4,D5,D6,D7
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article

// Thresholds
int thresholdUp = 900;
int thresholdDown = 700;

// Maximums
int maxWet = 0;
int minWet = 999;

// Pins
int moistureSensor = A0;
bool backlight = false;

void setup()
{
   // Set up LCD module
   lcd.begin (16, 2); // 16 x 2 LCD module
   lcd.setBacklightPin(3, POSITIVE); // BL, BL_POL
   lcd.setBacklight(LOW);
}

void updateMaxValues(int moistureValue) {
  if (moistureValue > maxWet) {
    maxWet = moistureValue;
  }
  if (moistureValue < minWet) {
    minWet = moistureValue;
  }
}

void printHeading(int value) {
  lcd.home(); // Set cursor to 0,0
  lcd.print("Plant Water: ");
  lcd.print(value);
}

void printMaxValues() {
  lcd.setCursor(0, 1);
  lcd.print(" MIN:");
  lcd.print(minWet);
  lcd.print(" MAX:");
  lcd.print(maxWet);
}

void printHighThresholdWarning() {
  lcd.setCursor(0, 1);
  lcd.print("ABOVE ");
  lcd.print(thresholdUp);
  lcd.print("!");
}

void printLowThresholdWarning() {
  lcd.setCursor(0, 1);
  lcd.print("BELOW ");
  lcd.print(thresholdDown);
  lcd.print("!");
}

void loop(){
  int moistureValue = analogRead(moistureSensor);

  updateMaxValues(moistureValue);
  printHeading(moistureValue);
  printMaxValues();

  if (moistureValue <= thresholdDown){
    printLowThresholdWarning();
  } else if (moistureValue >= thresholdUp){
    printHighThresholdWarning();
  }

  lcd.setBacklight(HIGH);
  delay(5000); //wait for a few seconds for backlight display
  lcd.setBacklight(LOW); // turn off backlight
  delay(15000); //wait for a while to re-read
}
