
#include <TinyWireM.h>
#include <TinyLiquidCrystal.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
TinyLiquidCrystal lcd(0);

// Parameters describing the current sense board
const float GAIN=100.0;
const float RESISTOR_VALUE=0.02;
const int Imax = 2500;
// Assumed reference voltage
const float vMax = 5.0;

// Accumulated ADC value
float aVal = 0.0;

void setup() {
  pinMode(PB3, INPUT);
  // set up the LCD
  lcd.begin(16, 2);            // our display has 16 cols, 2 rows
  lcd.setBacklight(HIGH);      // Turn on the backlight
  lcd.print("Digital Ammeter");  // Print a message to the LCD.
  lcd.setCursor(0, 1);
  lcd.print("v1.0 ATTiny85");
  delay(1000);
  lcd.clear();
  lcd.print("Imax = ");
  lcd.print(Imax);
  lcd.print("mA");
  lcd.setCursor(0, 1);
  lcd.print("Gain: ");
  lcd.print(GAIN);
  // Pre-load analogue value
  for (int i=0; i<100; i++) {
    int value = analogRead(3);
    aVal = 0.95*aVal+0.05*value;
    delay(5);
  }
  delay(400);
  lcd.clear();
}

void loop() {
  unsigned int value = analogRead(3);
  aVal = 0.95*aVal + 0.05*value;

  float mV = vMax * 1000.0 * aVal / 1023.0;
  
  float mA = mV/RESISTOR_VALUE/GAIN;
  
  lcd.setCursor(0, 0);
  lcd.print(mA);
  lcd.print(" mA    ");
  
  lcd.setCursor(0, 1);
  if ( mV > 999.99 ) {
    mV /= 1000.0;
    lcd.print(mV);
    lcd.print("V  (");
  } else {
    lcd.print(mV);
    lcd.print("mV (");
  }
  lcd.print(value);
  lcd.print(")    ");
  
  delay(5);

}

