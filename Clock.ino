/*ARDUINO BASED CLOCK WITH NOKIA 5110 LCD AND DS3231 MODULES.
# Auther : Raviraju Paidimala
# Email  : raviraju606@gmail.com */

#include <DS3231.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


/*  Fallowing pins of arduino are used to interface LCD,
    Pin 4 => as CLK
    Pin 3 => as Din
    Pin 2 => as DC
    Pin 1 => as CS
    Pin 0 => as RST
*/
Adafruit_PCD8544 display = Adafruit_PCD8544(4, 3, 2, 1, 0);
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;


void setup() 
{
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(7, LOW); // as GND for Display module
  digitalWrite(6, HIGH);// as BL for Display module
  digitalWrite(5, HIGH);// as +VCC for Display module
  
  pinMode(A3,OUTPUT);
  pinMode(A2,OUTPUT);
  digitalWrite(A3,HIGH);// as +VCC for RTC module
  digitalWrite(A2,LOW); // as GND for RTC module
  
  

 
  Wire.begin();
  display.begin();
  display.setContrast(60);
  display.display();
  delay(3000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
}


void loop()
{

  Disp1(); // Call page1
  Disp2(); // Call page2
  Disp3(); // Call page3


}




//***************** PAGE-1 ***************
void Disp1()
{
  int minute,hour; 

  minute=Clock.getMinute();
  hour=Clock.getHour(h12, PM);
  display.clearDisplay();
  drawlines();
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0,4);
  
  if(hour<10)
  {
    display.print("0");
  }
  display.print(hour,DEC);
  display.setTextSize(2);
  display.print(":");
  display.setTextSize(3);

  if(minute<10)
  {
    display.print("0");
  }
  display.print(minute,DEC);
  display.setTextSize(2);
  display.setCursor(4,30);

  if(h12)
  {
    if(PM)
    {
      display.println("  PM");
    }
    else
    {
      display.println("  AM");
    }
  }

  display.display();
  delay(5000);
}




//***************** PAGE-2***************

void Disp2()
{
  int date,month,year,dow;

  date=Clock.getDate();
  month=Clock.getMonth(Century);
  year=Clock.getYear();
  
  dow=dayOfWeek(year,month,date);

  display.clearDisplay();
  drawlines();
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0,4);
 

  if(dow==1)
  {
    display.print(" SUN");
  }

  if(dow==2)
  {
    display.print(" MON");
  }

  if(dow==3)
  {
    display.print(" TUE");
  }

  if(dow==4)
  {
    display.print(" WED");
  }

  if(dow==5)
  {
    display.print(" THU");
  }

  if(dow==6)
  {
    display.print(" FRI");
  }

  if(dow==7)
  {
    display.print(" SAT");
  }

  display.setTextSize(2);
  display.setCursor(12,30);
  if (date<10){
    display.print("0");
  }
  display.print(date,DEC);
  
  display.print("/");
  if (month<10){
    display.print("0");
  }
  display.print(month,DEC);

  display.display();  
  delay(5000);
}





//***************** PAGE-3 ***************
void Disp3()
{
  float temperature;
  temperature=Clock.getTemperature();

  display.clearDisplay();
  drawlines();
  display.clearDisplay();
  display.setCursor(0,0);

  display.print(" Temp:");
  display.setTextSize(3);
  display.setCursor(0,20);
  display.print(temperature,1);
  display.setTextSize(2);
  display.print("C");
  display.display();
  
  
  delay(5000);

}





byte dayOfWeek(int y, byte m, byte d)
{  
  static int t[] = {
    0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4  }; 
  y -= m < 3;
  return ((y + y/4 - y/100 + y/400 + t[m-1] + d) % 7) + 1; 
}




void drawlines()
{  
  for (int16_t i=0; i<display.width(); i+=4) 
  {
    display.drawLine(0, 0, i, display.height()-1, BLACK);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4)
  {
    display.drawLine(0, 0, display.width()-1, i, BLACK);
    display.display();
  }
  delay(20);
}
