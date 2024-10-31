// C++ code
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// create a new character"fire"
byte customChar0[8] = {
	0b00000,
	0b00100,
	0b01110,
	0b11111,
	0b11111,
	0b01110,
	0b00000,
	0b00000
};
// create a new character"heart"
byte customChar1[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

#define ADC_VREF 5  // in volt
#define ADC_RESOLUTION 1024.0 
#define PIN_TMP A0
#define BUZZER_PIN  13

void setup()
{
  lcd.init();
  lcd.backlight();
  
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.print("Hello!");
}


void loop()
{
 
  delay(1000);
  // read TMP sensor
  int adcVal = analogRead(PIN_TMP);
  // convert the ADC value to voltage
  float voltage = adcVal * (ADC_VREF / ADC_RESOLUTION);
  // convert the voltage to the temperature in Celsius
  float tempC = (voltage - 0.5) * 100;
  
  if(tempC <= 40)
      {
    	noTone(BUZZER_PIN);  // buzzer is off
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("The house is ");
    	lcd.setCursor(0,1);
    	lcd.print("safe");
    	lcd.createChar(1, customChar1); // create a new character
        lcd.setCursor(5, 1); // move cursor to (5, 1)
        lcd.write((byte)1);  // print the custom char at (5, 1)
    	
      }
  else
      {
    	tone(BUZZER_PIN,200); // buzzer is on
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("The house is on ");
    	lcd.setCursor(0,1);
    	lcd.print("fire");
    	lcd.createChar(0, customChar0); // create a new character
        lcd.setCursor(5, 1); // move cursor to (5, 1)
        lcd.write((byte)0);  // print the custom char at (5, 1)
        
    	
    
      }
  
  
}