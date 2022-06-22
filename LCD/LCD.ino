#include <LiquidCrystal.h> // Contains LiquidCrystal Library
#include <FlexiTimer2.h> // Contains FlexiTimer2 Library

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int tempPin = 4; // define the pin of temperature sensor
float tempVal; // define a variable to store temperature value
int hour, minute, second; // define variables stored record time

int ThermistorPin = 4;
int Vo;
double R1 = 10000;
double logR2, R2, T;                                                             // for thermistor temperature
double c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void setup() {
 lcd.begin(16, 2); // set up the LCD's number of columns and rows
 startingAnimation(); // display a dynamic start screen
 FlexiTimer2::set(1000, timerInt); // configure the timer and interrupt function
 FlexiTimer2::start(); // start timer
 Serial.begin(9600); // initialize serial port with baud rate 9600
 Serial.println("UNO is ready!"); // print the string "UNO is ready!"
 Serial.println("Input hour,minute,second to set time.");
}

void loop() {
 // Get temperature
 tempVal = setTemp();
 if (second >= 60) { // when seconds is equal to 60, minutes plus 1
 second = 0;
 minute++;
 if (minute >= 60) { // when minutes is equal to 60, hours plus 1
 minute = 0;
 hour++;
 if (hour >= 24) { // when hours is equal to 24, hours turn to zero
hour = 0;
 }
 }
 }

 lcdDisplay(); // display temperature and time information on LCD

delay(200);
}

double setTemp(){
   Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0;

  return T;
}



void startingAnimation() {
 for (int i = 0; i < 16; i++) {
 lcd.scrollDisplayRight();
 }
 lcd.print("Welcome Ngwesse...");
 for (int i = 0; i < 16; i++) {
 lcd.scrollDisplayLeft();
 delay(300);
 }
 lcd.clear();
}


// the timer interrupt function of FlexiTimer2 is executed every 1s
void timerInt() {
 second++; // second plus 1
}



// serial port interrupt function
void serialEvent() {
 int inInt[3]; // define an array to save the received serial data
 while (Serial.available()) {
 for (int i = 0; i < 3; i++) {
 inInt[i] = Serial.parseInt(); // receive 3 integer data
 }
 // print the received data for confirmation
 Serial.print("Your input is: ");
 Serial.print(inInt[0]);
 Serial.print(", ");
 Serial.print(inInt[1]);
 Serial.print(", ");
 Serial.println(inInt[2]);
 // use received data to adjust time
 hour = inInt[0];
 minute = inInt[1];
 second = inInt[2];
 // print the modified time
 Serial.print("Time now is: ");
 Serial.print(hour / 10);
 Serial.print(hour % 10);
 Serial.print(':');
 Serial.print(minute / 10);
Serial.print(minute % 10);
 Serial.print(':');
 Serial.print(second / 10);
 Serial.println(second % 10);
 }
}


// function used by LCD1602 to display time and temperature
void lcdDisplay() {
 lcd.setCursor(0, 0); // set the cursor to (0,0) (first column,first row).
 lcd.print("TEMP: "); // display temperature information
 lcd.print(tempVal);
 lcd.print("C");
 lcd.setCursor(0, 1); // set the cursor to (0,1) (first column,second row)
 lcd.print("TIME: "); // display time information
 lcd.print(hour / 10);
 lcd.print(hour % 10);
 lcd.print(':');
 lcd.print(minute / 10);
 lcd.print(minute % 10);
 lcd.print(':');
 lcd.print(second / 10);
 lcd.print(second % 10);
}
