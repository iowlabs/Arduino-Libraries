#include <Wire.h>
#include "rgb_lcd.h"
#include <SharpIR.h>

#define ir_1 A0
#define ir_2 A1

#define model_1 20150
#define model_2 1080

SharpIR sharp_1(ir_1, 25, 93, model_1);
SharpIR sharp_2(ir_2, 25, 93, model_2);

// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

rgb_lcd lcd;

void setup(void)
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // set up IR
  pinMode (ir_1, INPUT);
  pinMode (ir_2, INPUT);
}
 
void loop(void) 
{
  delay(1000);
  unsigned long time_b = millis(); // takes the time before the loop on the library begins
  double h_1 = sharp_1.distance();
  double h_2 = sharp_2.distance();
  
  // Print a message to the LCD.
  lcd.clear();
  lcd.print(h_1);
  lcd.display();
  delay(1000);
}
