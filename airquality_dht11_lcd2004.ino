// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
int lastReadTime;
int airQuality;
long int interval = 10*100;
#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//declare variables
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  dht.begin();
lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 airQuality = analogRead(5);       // read analog input pin 5
 
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  long currentTime=millis();
  if (currentTime>lastReadTime+interval){
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Humidity: "); 
    lcd.print(h);
    lcd.print(" %\t");
    lcd.setCursor(2,1);
    lcd.print("Temperature: "); 
    lcd.print(t);
    lcd.print(" *C");
    lcd.setCursor(0,2);
    lcd.print(airQuality, DEC);  // prints the value read
    lcd.setCursor(2,3);
    lcd.print("   Halil   ")
    lastReadTime=millis();
    }
 
  }
  //////////////////////////humidity////////////////////////////////////////////////
if (h<40){
  digitalWrite(2,HIGH); // humidifier device 
  digitalWrite(5,HIGH);// red  Color of light according to humidity which color should we select ? ()
 digitalWrite(6,HIGH); // green color   TOTAL RED+GREEN = YELLOW
} else {
  digitalWrite (2,LOW); // humidifier device
digitalWrite(7,HIGH); // Blue COLOR 
 digitalWrite(6,HIGH); // green color   TOTAL blue+GREEN = Cyan
digitalWrite(5,LOW);// red  Color of light according to humidity which color should we select ? ()
}

if (h>50){
  digitalWrite(3, HIGH);// air Conditioner 
digitalWrite(5,HIGH);// red  Color of light according to humidity which color should we select ? ()
digitalWrite(7,HIGH); // Blue COLOR  RED+BLUE= MAGENTA
} else {
  digitalWrite(3, LOW);// air Conditioner
digitalWrite(7,HIGH); // Blue COLOR 
 digitalWrite(6,HIGH); // green color   TOTAL blue+GREEN = Cyan
digitalWrite(5,LOW);// red  Color of light according to humidity which color should we select ? ()
}
////////////////////////////////////temprature////////////////////////////////
if (t > 28){
  digitalWrite(3, HIGH);// air Conditioner 
 digitalWrite(9,HIGH);// red  Color of light according to humidity which color should we select // RED COLOR FOR HOT WEATHER
} else {
  digitalWrite(3, LOW);// air Conditioner
  digitalWrite(10, HIGH);// GREEN COLOR 
  digitalWrite(9, LOW);
}
if (t<25){
  digitalWrite(4, HIGH);// heater 
  digitalWrite(9,HIGH);// red  Color of light according to temp. which color should we select ? ()
  digitalWrite(11,HIGH); // Blue COLOR  RED+BLUE= MAGENTA

} else {
  digitalWrite(4, LOW);// heater
  digitalWrite(9,LOW);// red  Color 
  digitalWrite(11,LOW); // Blue COLOR  
 digitalWrite(10, HIGH);// GREEN COLOR 
}
}
/// pin 2- humiidifier      3-A/C            4- HEATER
// pin  5- red              6- green         7- Blue
// pin  9- red              10- green         11 blue

// etmega chip pins 2-3-4 = 4.-5.-6th pins           5-6-7 = 11-12-13             9-10-11= 15-16-17
