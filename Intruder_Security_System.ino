/* A Simple Intruder Security System*/
/*Compoments : ATMEGA 328, Servo motor, Ultrasonic Sensor, Buzzer and LCD*/
#include <Servo.h>
#include <LiquidCrystal.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
// Pin Definition for Ultrasonic Sensor
#define trigger 11 // Trigger Pin defined as 11
#define echo 2 // Echo Pin  defined as pin 2
#define Buzzer 3 // Buzzer Pin defined as 3
#define Relay 10 // Relay pin as 10 (Relay is connected in NO connection
const int rs = 10, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float time;
float distance = 0;
char LCDmsg[21];

void setup() {
  lcd.begin(16, 2);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin (9600); // Begin Serial Communication
  pinMode (trigger, OUTPUT);
  pinMode (echo, INPUT);
  pinMode (Buzzer, OUTPUT);
}

void loop() {
  // Ultrasonic Sensor Distance Detection Program
  digitalWrite (trigger, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger, LOW);
  time = pulseIn (echo, HIGH);
  distance = (time * 0.034) / 2;
  Serial.println(distance);
  lcd.setCursor(0,0);
  lcd.print ("Security System");


  // Actuation Program
  if ( distance < 10) // Distance less than 10cm
  {
    //Buzzer High
    digitalWrite (Buzzer, HIGH);
    lcd.setCursor(0,0);
    lcd.print ("Intruder Alert ");
    lcd.setCursor (0,1);
    dtostrf (distance,3,1,LCDmsg);
    lcd.print ("Distance=");
    lcd.print (" ");
    lcd.print (distance);
    
    
    
    // Sweep function blade
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    
  }
  else
  {
    digitalWrite (Buzzer, LOW);
    lcd.setCursor (0,0);
    lcd.print ("Security System");
    lcd.setCursor (0,1);
    dtostrf (distance,4,1,LCDmsg);
    lcd.print("Distance=");
    lcd.print(" ");
    lcd.print (distance);
    
    
  }
}
