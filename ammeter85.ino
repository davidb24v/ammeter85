
#include <TinyWireM.h>
#include <TinyLiquidCrystal.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
TinyLiquidCrystal lcd(0);

const float GAIN=100.0;

// Simple function to get amount of RAM free
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

// We'll use the median value over 11 readings
const int NVALS=20;

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
  lcd.print("Max Current 50mA");
  lcd.setCursor(0, 1);
  lcd.print("Gain: ");
  lcd.print(GAIN);
  int value = analogRead(3);
  delay(1000);
  lcd.clear();
}

int count = 0;
float aVal = 0.0;

void loop() {
  unsigned int value = analogRead(3);
  delay(25);
  aVal = 0.95*aVal + 0.05*value;
  count++;
  if ( count < NVALS ) return;
  count = 0;

  // With 2 x 5% 100kR I get Vcc/2.1, not Vcc/
  float mV = 5.0 * 1000.0 * aVal / 1023.0;
  
  float mA = mV/GAIN;
  
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
  lcd.print(")  ");
  
  delay(500);

}

