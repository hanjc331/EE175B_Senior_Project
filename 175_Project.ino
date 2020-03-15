#include <TimerOne.h>

#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int analogPin = A1;

int Dcycle = 0;

int Bpin3 = 3;
int Pwmpin = 10;
int d=0;
int Bstat3 = 0;

int Bstat4 = 0;
int Bstat5 = 0;
int i=0;
double Read = 0;
double val = 0;
double targetval = 2.57;
int secdelay = 10 ;
void setup() {
  Serial.begin(9600); // setup serial
  
  pinMode(Pwmpin, OUTPUT);
  
  pinMode(Bpin3,INPUT_PULLUP);

  Timer1.initialize(20); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.pwm(Pwmpin,Dcycle,20); 
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Volage(V): ");
  lcd.setCursor(0,1);
  Read = analogRead(analogPin);
  val = Read * 0.0049;
  //Serial.print(val);
  //Serial.print("\n");
//  lcd.print(val);
    Serial.print(Dcycle);
    Serial.print("\n");
  if (i<secdelay){
  delayMicroseconds(50);
  i++;
  }
   // Bstat3 = digitalRead(Bpin3);

   if (Dcycle<490 && val<targetval && i>=secdelay){
    Dcycle=Dcycle+10;
    Timer1.pwm(Pwmpin,Dcycle,20);
    i=0;
   }
   if (val>targetval + .15){
  //  Serial.print(val);
  //  Serial.print("\n");
    Dcycle=0;
    Timer1.pwm(Pwmpin,Dcycle,20);
   }
   else if (val>targetval+.05 && Dcycle >=10){
    Dcycle=Dcycle-10;
    Timer1.pwm(Pwmpin,Dcycle,20);
    i=0;
   }

   Bstat3 = digitalRead(Bpin3);
   if (Bstat3==LOW){
   delay(400);

    if (d==0){
      Dcycle=0;
      targetval= .15;
      Timer1.pwm(Pwmpin,Dcycle,20);
      d=1;
        //  Serial.print("button pushed set to 3v");
    }
    else if (d==1){
      targetval= .5;
      d=0;
       //   Serial.print("button pushed set to 5v");
    }
   }



}
