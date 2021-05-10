#include <Wire.h>
#include "RTClib.h"
//#include <LiquidCrystal.h>

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//LiquidCrystal lcd(8 ,6, 7,11,12,13);

const byte interruptPin_S1 = 73;
const byte interruptPin_S2 = 74;
const byte ledPin_B = 77;
int alarmHour = 1;
int alarmMinute = 56;
int keepHour = 0;
int keepMinute = 0;
int state = 0;



void setup () {
  //  lcd.begin(16, 2);
  //  lcd.setCursor(3,0);
  //  lcd.print("RTC Clock");
  //  delay(3000);
  //  lcd.clear();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  pinMode(ledPin_B, OUTPUT);
  pinMode(interruptPin_S1, INPUT_PULLUP);
  pinMode(interruptPin_S2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin_S1),changeState, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin_S2),addUp, CHANGE);

  LEDPIN_Init();
  LED_Init();
  
  Serial.begin(9600);
}


void loop () {
    DateTime now = rtc.now();
//    lcd.clear();
//    lcd.setCursor(3,0);

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
    Serial.println(state);
    Serial.print(keepHour);    
    Serial.print(':');
    Serial.println(keepMinute);
    Serial.print(alarmHour);    
    Serial.print(':');
    Serial.println(alarmMinute);
    
    if (state == 0) {
      String dateString = (String(now.day(), DEC) + "/" + String(now.month(), DEC) + "/" + String(now.year(), DEC));
      int dateLen = dateString.length() + 1;
      char dateArray[dateLen];
      dateString.toCharArray(dateArray, dateLen);
      String timeString = (String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + ":" + String(now.second(), DEC));
      int timeLen = timeString.length() + 1;
      char timeArray[timeLen];
      timeString.toCharArray(timeArray, timeLen);   
      LED_P8x16Str(24,0,dateArray);
      LED_P8x16Str(36,3,daysOfTheWeek[now.dayOfTheWeek()]);
      LED_P8x16Str(32,6,timeArray);
    } else {
      String alarmString = (String(keepHour) + ":" + String(keepMinute));
      int alarmLen = alarmString.length() + 1;
      char alarmArray[alarmLen];
      alarmString.toCharArray(alarmArray, alarmLen);
      LED_P8x16Str(0,0,"set alarm clock");
      LED_P8x16Str(10,3,"hour : minute");      
      LED_P8x16Str(0,6,"               ");
      LED_P8x16Str(48,6,alarmArray);
    }
    
    
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
    if ((alarmHour == now.hour()) && (alarmMinute == now.minute())) {
      blink();
    } else {
      delay(1000);      
    }
}


void changeState() {
  if (state < 2) {
    state ++;
  } else {
    state = 0;
    alarmHour = keepHour;
    alarmMinute = keepMinute;
    LED_P8x16Str(0,0,"               ");
    LED_P8x16Str(0,3,"               ");
  }
}


void addUp() {
  if (state == 1) {
    if (keepHour < 23) {
      keepHour ++;
    } else {
      keepHour = 0;
    }
  }   
  if (state == 2) {
    if (keepMinute < 59) {
      keepMinute ++;
    } else {
      keepMinute = 0;
    }
  }
}


void blink() {
  Serial.println("blink");
  digitalWrite(ledPin_B, HIGH);
  delay(500);
  digitalWrite(ledPin_B, LOW);
  delay(500);
}
