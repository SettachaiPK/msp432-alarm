#include <Wire.h>
#include "RTClib.h"
//#include <LiquidCrystal.h>

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//LiquidCrystal lcd(8 ,6, 7,11,12,13);


void setup () {
  //  lcd.begin(16, 2);
  //  lcd.setCursor(3,0);
  //  lcd.print("RTC Clock");
  //  delay(3000);
  //  lcd.clear();
  rtc.begin();
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.begin(9600);
}


void loop () {
    DateTime now = rtc.now();
//    lcd.clear();
//    lcd.setCursor(3,0);

    Serial.print(now(),BIN);
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.println(' ');
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(',');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
//    lcd.print(now.day(), DEC);
//    lcd.print("/");
//    lcd.print(now.month(), DEC);
//    lcd.print("/");
//    lcd.print(now.year(), DEC);
//    lcd.setCursor(1,5);
//    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    lcd.print(",");
//    lcd.print(now.hour(), DEC);
//    lcd.print(":");
//    lcd.print(now.minute(), DEC);
//    lcd.print(":");
//    lcd.print(now.second(), DEC);
    delay(5000);
}
