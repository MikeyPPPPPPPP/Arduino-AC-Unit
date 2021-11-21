#include <LiquidCrystal.h>
#include <dht.h>


#define dht_apin A0 // Analog Pin sensor is connected to
int up = 0;
int down = 0;
int fan = 0;

dht DHT;

int setTemp = 70;
const int digitalUpButtonPin = 8;
const int digitalDownButtonPin = 9;
const int digitalFanPin = 53;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


void increas() {
    setTemp = setTemp + 1;
}

void decreas() {
    setTemp = setTemp - 1;
}

void setup(){
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  //Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  pinMode(digitalUpButtonPin, INPUT);
  pinMode(digitalDownButtonPin, INPUT);
  pinMode(digitalFanPin, OUTPUT);
  lcd.begin(16, 2);
  
 
}//end "setup()"
 
void loop(){
    up = digitalRead(digitalUpButtonPin);
    down = digitalRead(digitalDownButtonPin);
    
    
    //Start of Program 
    if (up == HIGH) {
      increas();
    }
    if (down == HIGH) {
      decreas();
    }
    if (abs((1.8 * DHT.temperature + 32)) > setTemp){
      digitalWrite(digitalFanPin, HIGH);
    } else {
      digitalWrite(digitalFanPin, LOW);
    }
    lcd.setCursor(0, 1);
    DHT.read11(dht_apin);
    Serial.println(setTemp);
    
    //String out = String(1.8 * DHT.temperature + 32)+"F "+String(DHT.humidity)+"H "+String(setTemp);
    String out = String(abs(1.8 * DHT.temperature + 32))+"F Set"+String(setTemp);
    lcd.print(out);
    
    delay(1000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop(
