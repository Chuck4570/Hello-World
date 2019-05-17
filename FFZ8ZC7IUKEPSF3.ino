   //////////////////////////////////////////////
  //        Arduino Soil Moisture Sensor      //
 //            with NOKIA 5110 LCD           //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////


#include <LCD5110_Graph.h> // THE LIBRARY I AM USING IS THIS:  http://www.rinkydinkelectronics.com/library.php?id=47


LCD5110 lcd(8,9,10,12,11);

extern unsigned char BigNumbers[];
extern uint8_t ui[];

int sensorPin = A0;  
int sensorValue = 0;  
int percent = 0;
String percentString ="0";
int stringLength = 0;

void setup() {
  lcd.InitLCD();
  lcd.setFont(BigNumbers);
  delay(1000);
}

void loop() {
  lcd.clrScr();
  lcd.drawBitmap(0, 0, ui, 84, 48);
  sensorValue = analogRead(sensorPin);
  percent = convertToPercent(sensorValue);
  percentString = String(percent);
  stringLength = percentString.length();
  displayPercent(stringLength);
  
  lcd.update();
  delay(1000);
}

int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 350, 0, 100);
  if(percentValue>100)
    percentValue = 100;
  return percentValue;
}

void displayPercent(int length)
{
  switch(length)
  {
    case 1:  lcd.print(percentString,38,19); break;
    case 2:  lcd.print(percentString,24,19); break;
    case 3:  lcd.print(percentString,10,19); break;
    default:  lcd.print(percentString,0,19); break;
  }
}

