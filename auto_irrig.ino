#include<LiquidCrystal.h>
#include<math.h>
/*
  Example 10: 7 Segment Display (Digital Display)
  Sidekick Basic Kit for TI LaunchPad
  
  Here we will use a component that include 7 LEDs that are arranged
  in a grid so that we can form numbers and letters. This is one of the
  most basic types of displays, but have since been replaced by more 
  popular LCDs (Liquid Crystal Displays), LED matrices,  and other display 
  technologies. 
  
  We will display the different numbers in a single digit countdown 
  sequence.  It is also possible to form letters, but we will just cover 
  numbers 0-9 in the example. 
  
  Hardware Required:
  * TI LaunchPad
  * Breadboard BoosterPack
  * Breadboard
  * 7 Segment Display
  * 9x Jumper Wires
  * 8x 330 ohm resistors (optional)
  
  This example code is in the public domain.
*/

// Define the LED digit patterns for 0 - 9 in a 2 dimensional array.
// The 2D array (an array of arrays or a matrix) has 10 arrays that each 
// contain 7 values. 
// Note that these patterns are for common cathode displays. For common 
// anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
// Common Anode version
/*byte seven_segment_digits[10][7] = { { 0,0,0,0,0,0,1 }, // display '0'
                                     { 1,0,0,1,1,1,1 }, // display '1'
                                     { 0,0,1,0,0,1,0 }, // display '2'
                                     { 0,0,0,0,1,1,0 }, // display '3'
                                     { 1,0,0,1,1,0,0 }, // display '4'
                                     { 0,1,0,0,1,0,0 }, // display '5'
                                     { 0,1,0,0,0,0,0 }, // display '6'
                                     { 0,0,0,1,1,1,1 }, // display '7'
                                     { 0,0,0,0,0,0,0 }, // display '8'
                                     { 0,0,0,1,1,0,0 }  // display '9'
                                   };*/
const int sensor_pin = A7;	/* Soil moisture sensor O/P pin */   
LiquidCrystal lcd(2,10,11,12,13,14);

// Common Cathode version
byte seven_segment_digits[10][7] = { { 1,1,1,1,1,1,0 }, // display '0'
                                     { 0,1,1,0,0,0,0 }, // display '1'
                                     { 0,0,0,1,1,1,0 },
                                     { 0,1,1,0,1,1,1 }, // display '2'
                                      // display '3'
                                     { 0,1,1,0,0,1,1 }, // display '4'
                                     { 1,0,1,1,0,1,1 }, // display '5'
                                     { 1,0,1,1,1,1,1 }, // display '6'
                                     { 1,1,1,0,0,0,0 }, // display '7'
                                     { 1,1,1,1,1,1,1 }, // display '8'
                                     { 1,1,1,0,0,1,1 }  // display '9'
                                   };


/* Connect the pins of the display accordingly. 
Only one of the VCC (Common Anode) / GND (Common Cathode) pins need to be 
connected to work, but it's ok to connect both if you want. 
///////////////TOP//////////////
   pin 1 : G (9)  pin 10: A (3)
   pin 2 : F (8)  pin 9 : B (4)
   pin 3 : VCC    pin 8 : VCC
   pin 4 : E (7)  pin 7 : C (5)
   pin 5 : D (6)  pin 6 : Dot (10)
/////////////BOTTOM/////////////
*/

/* In the setup function, we set our LED pins as OUTPUT.
 */
void setup() {  
  lcd.begin(16,2);
  
  
  pinMode(3, OUTPUT); // set segment A as output
  pinMode(4, OUTPUT); // set segment B as output
  pinMode(5, OUTPUT); // set segment C as output
  pinMode(6, OUTPUT); // set segment D as output
  pinMode(7, OUTPUT); // set segment E as output
  pinMode(8, OUTPUT); // set segment F as output
  pinMode(9, OUTPUT); // set segment G as output
  //pinMode(10, OUTPUT); // set dot as output
  for(int i = 3; i < 10; i++) { // start with segments off
    digitalWrite(i, HIGH);
  }
  Serial.begin(9600);
  //digitalWrite(10, HIGH);  // start with the dot off
}

/* In the loop section we will begin displaying the different numbers. 
 * Add delay() or sleep() to give some time between the numbers changing.
 */
void loop() {
  float moisture_percentage;int moist;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  
  
  
  if(moisture_percentage>0 &&moisture_percentage<40)
  {
    lcd.clear();
    lcd.write("Moisture = ");
    lcd.setCursor(11,0);
  lcd.write("00-40");
    int pin = 3;
    for (int segCount = 0; segCount < 7; ++segCount) {
      digitalWrite(pin, seven_segment_digits[2][segCount]);
      ++pin;
    }
    
    lcd.setCursor(0,1);
    lcd.write("MILLETS");
    
  }
  
 else if(moisture_percentage>40 &&moisture_percentage<60)
  {
    //digitalWrite(3,LOW);
    lcd.clear();
    lcd.write("Moisture = ");
    lcd.setCursor(11,0);
  lcd.write("40-60");
    lcd.setCursor(0,1);
    lcd.write("GROUNDNUT");
    int pin = 3;
    
    for (int segCount = 0; segCount < 7; ++segCount) {
      //digitalWrite(pin1, LOW);
      digitalWrite(pin, seven_segment_digits[1][segCount]);
      ++pin;
    }
  }
  
 else if(moisture_percentage>60)
  {
        
    lcd.clear();
    lcd.write("Moisture = ");
    lcd.setCursor(11,0);
  lcd.write("60+");
    lcd.setCursor(0,1);
    lcd.write("COTTON");
    int pin = 3;
    for (int segCount = 0; segCount < 7; ++segCount) {
      digitalWrite(pin, seven_segment_digits[3][segCount]);
      ++pin;
    }
    
  }  
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  delay(1000);
}
