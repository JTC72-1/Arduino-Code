// init rtc and aht10
// measure aht10 and read rtc
// goal 1: print both info in same line
#include <Adafruit_AHT10.h>
#include "Sodaq_DS3231.h"

char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
//year, month, date, hour, min, sec and week-day(starts from 0 and goes to 6)
DateTime dt(2022, 12, 20, 13, 46, 0, 3);


Adafruit_AHT10 aht;

void setup() {
 Serial.begin(57600);
 // put your setup code here, to run once:
 if (! aht.begin()) {
 Serial.println("Could not find AHT10? Check wiring");
 while (1) delay(10);
 }
 Serial.println("Timestamp, temp_c, rel_hum, light_intensity");
 Wire.begin();
 rtc.begin();
 rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above

}

void loop() {
 // put your main code here, to run repeatedly:
 sensors_event_t humidity, temp;
 aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
 DateTime now = rtc.now(); //get the current date-time
 Serial.println();
 Serial.print(now.month(), DEC);
 Serial.print('/');
 Serial.print(now.date(), DEC);
 Serial.print('/');
 Serial.print(now.year(), DEC);
 Serial.print(' ');
 Serial.print(now.hour(), DEC);
 Serial.print(':');
 Serial.print(now.minute(), DEC);
 Serial.print(':');
 Serial.print(now.second(), DEC);
 Serial.print(', ');
 Serial.print(temp.temperature);
 Serial.print(', ');
 Serial.print(humidity.relative_humidity);
 Serial.print(', ');
 float voltage = (analogRead(A1)/1023.0)*3.3;
 Serial.print(voltage);
 delay(500);
}
