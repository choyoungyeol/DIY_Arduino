#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <DHT.h>  //"DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define FanPin 32

#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;
#define lightPin 4

#define PHOTO A0
int Photo_Value = 0;
#define waterPin A1

void setup()
{
  pinMode(lightPin, OUTPUT);

  if (! rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    //Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }


  pinMode(FanPin, OUTPUT);

  Serial.begin(9600);
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("JNU Arduino!");
  delay(5000);
}


void loop()
{
  Photo_Value = analogRead(PHOTO);
  float pv_value = float(Photo_Value * 5) / 1023;
  float Rp = (10 * pv_value) / (5 - pv_value);
  float y = (log10(200 / Rp)) / 0.7;
  float Ea = pow(10, y);


  int water_value = analogRead(waterPin);
  int water_content = map(water_value, 984, 298, 0, 100);
 

  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  

  if (t >= 25) {
    digitalWrite(FanPin, HIGH);
  } else {
    digitalWrite(FanPin, LOW);
  }


  DateTime now = rtc.now();

  if ((now.hour() >= 6 ) && (now.hour() <= 18)) {
    if (Ea <= 200) {
      analogWrite(lightPin, 255);
    } else {
      analogWrite(lightPin, 0);
    }
  } else {
    analogWrite(lightPin, 0);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(now.year());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.day());

  lcd.setCursor(0, 1);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pa: ");
  lcd.print(Photo_Value);

  lcd.setCursor(0, 1);
  lcd.print("lx: ");
  lcd.print(Ea);
  lcd.print(" lux");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.print(h);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water: ");
  lcd.print(water_value);

  lcd.setCursor(0, 1);
  lcd.print("WC: ");
  lcd.print(water_content);
  lcd.print(" %");
  delay(5000);

  Serial.print(Ea);   //광도
  Serial.print(",");
  Serial.print(water_content);  //수분함량
  Serial.print(",");
  Serial.print(h);   //습도
  Serial.print(",");
  Serial.println(t);   //온도
}
