

#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#include <Wire.h>
#include <DS3231.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

DS3231 clock;
RTCDateTime dt;
int tempPin = 0;
int sensorPin = 2;
int lcdPin = 6;
int ledPin =13;
DHT_nonblocking dht_sensor( sensorPin, DHT_SENSOR_TYPE );
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

byte percent[] = {
  B11001,
  B11011,
  B00010,
  B00110,
  B01100,
  B01000,
  B11011,
  B10011
};
byte degree[] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

byte progress1[] = {
  B01111,
  B11000,
  B10011,
  B10111,
  B10111,
  B10011,
  B11000,
  B01111
};

byte progress2[] = {
  B11000,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B00000,
  B11000
};

byte progress3[] = {
  B11111,
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B00000,
  B11111
};

byte progress4[] = {
  B11110,
  B00011,
  B11001,
  B11101,
  B11101,
  B11001,
  B00011,
  B11110
};

byte strich[] = {
  B00010,
  B00010,
  B00010,
  B00010,
  B00010,
  B00010,
  B00010,
  B00010
};


byte strichl[] = {
  B01000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01000,
  B01000
};


void setup()
{
  /*lcd.begin(cols, rows)
    lcd: a variable of type LiquidCrystal
    cols: the number of columns that the display has
    rows: the number of rows that the display has 
  */
  pinMode(lcdPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(lcdPin, HIGH);
  digitalWrite(ledPin, LOW);
  lcd.begin(16, 2);
  lcd.createChar(0, percent); 
  lcd.createChar(1, degree);
  lcd.createChar(2, progress1);
  lcd.createChar(3, progress2);
  lcd.createChar(4, progress3);
  lcd.createChar(5, progress4);
  lcd.createChar(6, strichl);  
  lcd.createChar(7, strich);

  lcd.home(); 
  lcd.setCursor(0,0);
  lcd.print("Weather Station");
/*  lcd.setCursor(2,1);
  lcd.print("loading.");
  delay(500);
  lcd.print(".");
  delay(500);  
  lcd.print(".");
  delay(500);
  lcd.setCursor(9,1);
  lcd.print("    ");
  delay(500);
  lcd.setCursor(9,1);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(1000);            */
  delay(500);
  lcd.setCursor(12,1);
  lcd.print("  0");
  lcd.write((byte)0);
  lcd.setCursor(0,1);
  delay(200);
  lcd.write((byte)2);
  delay(200);
  for(int i=1; i<10; i++) {
    lcd.write((byte)3);
    delay(150);
    lcd.setCursor(i,1);
    lcd.write((byte)4);
    lcd.setCursor(12,1);
    lcd.print(" ");
    lcd.print(i*10);
    lcd.setCursor(i+1,1);
    delay(150);
  }
  lcd.setCursor(10,1);
  lcd.write((byte)3);
  delay(200);
  lcd.setCursor(10,1);
  lcd.write((byte)4);
  delay(200);  
  lcd.write((byte)5);
  delay(200);
  lcd.setCursor(12,1);
  lcd.print("100");  
  lcd.setCursor(11,1);
  delay(1000); 
    

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initialize");
  lcd.setCursor(0, 1);
  lcd.print("RTC module");
  clock.begin();
  //clock.setDateTime(__DATE__, __TIME__);
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.write((byte)7);
  lcd.print("Temp:-----");
  lcd.write((byte)1);
  lcd.print("C");
  lcd.write((byte)6);
  lcd.setCursor(0, 1);
  lcd.write((byte)7);
  lcd.print("Humd:-----");
  lcd.write((byte)0);
  lcd.print(" ");
  lcd.write((byte)6);
//  digitalWrite(ledPin, HIGH);
}


/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every one second. */
  if( millis( ) - measurement_timestamp > 1000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}


void loop()
{
  //digitalWrite(ledPin, !digitalRead(ledPin));
  dt = clock.getDateTime();
  float temperature;
  float humidity;
  /**int h = dt.hour; */

//  int r1 = random(2,7);
//  int r2 = random(2,7);
//  int r3 = random(2,7);
//  int r4 = random(2,7);
//  int r5 = random(2,7);
//  int r6 = random(2,7);
/*  Measure temperature and humidity. If the function returns true,
    then a measurement is available. */  
  if( measure_environment(&temperature, &humidity) == true) {
    digitalWrite(ledPin, HIGH);
    lcd.setCursor(6,0);
    lcd.print(temperature);    
    lcd.setCursor(6, 1);
    lcd.print(humidity);
    } else{
      digitalWrite(ledPin, LOW); 
    }

  lcd.setCursor(14,0);
//  lcd.write((byte)r1);
//  lcd.write((byte)r2);
//  lcd.write((byte)r3);
  lcd.print("  ");
  lcd.setCursor(14, 0);
  if(dt.hour < 10) {
    lcd.print("0");
    lcd.print(dt.hour);
  } else {
      lcd.print(dt.hour);
  }
  lcd.setCursor(14,1);
//  lcd.write((byte)r4);
//  lcd.write((byte)r5);
//  lcd.write((byte)r6);
  lcd.print("  ");
  lcd.setCursor(14, 1);
  if(dt.minute < 10) {
    lcd.print("0");
    lcd.print(dt.minute);    
  } else {
    lcd.print(dt.minute);
  }
  /** if(h > 7 && h < 21) {
    digitalWrite(lcdPin, HIGH);
  } else{
    digitalWrite(lcdPin, LOW);
  } **/
  digitalWrite(lcdPin, LOW);
  delay(5000);

}
