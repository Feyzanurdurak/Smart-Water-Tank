/*
 * Project Name    :  Smart Water Tank
 * Revision Date   :  26.12.2021
 * Author          :  Feyza Nur DURAK
 
 //----------------------------------------------------------------------------------------------------------------------------------------------------------
 Purpose           :  Measuring the water level, informing the changes in the water level and warning at critical levels.
 //----------------------------------------------------------------------------------------------------------------------------------------------------------
 System Input      :
                    1) Water Level Sensor : Measuring the water level
                    2) Resistance         : Prevent high current
 System Output     :
                    1) LED                : To alert with color
                    2) Buzzer             : To alert with sound
                    3) LCD screen         : To alert with writing
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
System Work        : The water level in the tank is measured with the water sensor, when it falls below certain levels, 
                     it gives a warning with led and bell and the water level is written on the LCD screen.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
*/

// Treshold values.
int lowerThreshold = 420;      
int upperThreshold = 520;    

// Sensor pins
#define sensorPower 7
#define sensorPin A0
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Value for storing water level
int val = 0;

// Declare pins to which LEDs are connected
int redLED = 2;
int yellowLED = 3;
int greenLED = 4;
int buzzerPin = 9;

//put your setup code here, to run once:
void setup() 
{
  Serial.begin(9600);                            // Sets the baud rate for serial data transmission.
  pinMode(sensorPower, OUTPUT);                  // Sensor power defined as OUTPUT.
  digitalWrite(sensorPower, LOW);      
  pinMode(buzzerPin, OUTPUT);                    // Buzzer pin defined as OUTPUT.
  lcd.begin();

  
  // Set LED pins as an OUTPUT
  pinMode(redLED, OUTPUT);                       
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Initially turn off all LEDs
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}

// put your main code here, to run repeatedly:
void loop() 
{
  int level = readSensor();                       // Level is become equel to readSensor.

  if (level == 0)                                 // If the water level is 0, the leds are OFF.
  {
    Serial.println("Water Level: Empty"); 
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    lcd.setCursor(0,0);
    lcd.print("Waterlevel:Empty");                // "empty" is written on the LCD screen.
    lcd.setCursor(0,1);
    lcd.print("Please add water!");               // "Please add water!" is written on the LCD screen.
    delay(2000);
    
  }

  else if (level > 0 && level <= lowerThreshold)  // If water level is between 0-lowerThreshold, red led is ON, buzzer is ON for 1 second.
  {
    Serial.println("Water Level: Low");
    digitalWrite(redLED, HIGH);                   // Red LED led is ON.
    digitalWrite(yellowLED, LOW);                  
    digitalWrite(greenLED, LOW);
    digitalWrite(buzzerPin, HIGH);                // Buzzer is ON.
    delay(1000);                                  // Wait for a 1 second.
    digitalWrite(buzzerPin,LOW);                  // Buzzer is OFF.
    delay(200);                                   // Wait for a 0,2 second.
    lcd.setCursor(0,0);
    lcd.print("Water level: LOW ");               // "Low" is written on the LCD screen.
    lcd.setCursor(0,1);
    lcd.print("Please add water!");               // "Please add water!" is written on the LCD screen.
    delay(2000);
  }
  

  else if (level > lowerThreshold && level <= upperThreshold)  // If water level is between lowerThreshold-upperThreshold, yellow led is ON.
  {
    Serial.println("Water Level: Medium");         
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);               // Yellow LED is ON.
    digitalWrite(greenLED, LOW);
    lcd.setCursor(0,0);
    lcd.print("Waterlevel:MEDIUM ");             // "Medium" is written on the LCD screen.
    lcd.setCursor(0,1);
    lcd.print("Enough Water");                   // "Enough Water" is written on the LCD screen.
    delay(2000);
  }
  
  else if (level > upperThreshold)               // If water level is greater than upperThreshold, green led is ON, buzzer is on for 2 second.
  {
    Serial.println("Water Level: High");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);                // Green LED is ON.
    digitalWrite(buzzerPin, HIGH);               // Buzzer is ON.
    delay(500);                                 // Wait for a 0,5 second.
    digitalWrite(buzzerPin,LOW);                 // Buzzer is OFF.
    delay(2000);                                 // Wait for a 2 second.
    lcd.setCursor(0,0);
    lcd.print("Waterlevel:HIGH ");               // "HIGH" is written on the LCD screen
    lcd.setCursor(0,1);
    lcd.print("Do not add water");               // "Do not add water" is written on the LCD screen.
    delay(2000);
  }
  delay(1000);
}


int readSensor() {                               //This is a function used to get the reading
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}
