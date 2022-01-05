
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN A4
#define DHTTYPE DHT11
//#define fan_out 11
//#define lamp_out 10
DHT dht(DHTPIN,DHTTYPE);
SoftwareSerial s(7,6);
bool status = false;
unsigned long read_ir;
unsigned long read_dht;
//unsigned long send_data;

float h;
float t;
float hic;
int Auto; //8
int lamp; //9
int fan; //10
int light;//13
//int data3;

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {

  read_ir=0;
  read_dht=0;
  //send_data=0;
  
  pinMode(A2,INPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A5,OUTPUT);
 // pinMode(10,OUTPUT);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A3,HIGH);
  digitalWrite(A5,LOW);
  
  s.begin(9600);
  Serial.begin(9600);
  lcd.begin(20, 4);
  
  
  // Print a message to the LCD.
  lcd.print("IoT Home Automation");

  dht.begin();
}


void loop() {
  
  unsigned long curr_millis=millis();

  receive_json();

  if(curr_millis-read_ir>=500){
    perform_ir();
    read_ir=curr_millis;
  }

  if(curr_millis-read_dht>=2000){
    perform_dht();
    read_dht=curr_millis;
  }

  

  
}

void perform_ir() {
  if(analogRead(A2)<250){
    status= !status;
  }
  
  if(Auto==1){
    digitalWrite(8,HIGH);
    lcd.setCursor(0,2);
    lcd.print("Auto  ");
    
    if(status==false){
      digitalWrite(9,LOW);
      lcd.setCursor(0,3);
      lcd.print("lamp off");
    }
    else{
      digitalWrite(9,HIGH);
      lcd.setCursor(0,3);
      lcd.print("lamp on ");
    }
    
    if(light==1){
      digitalWrite(13,HIGH);
      lcd.setCursor(9,2);
      lcd.print("Led on ");
    }
    else{
      digitalWrite(13,LOW);
      lcd.setCursor(9,2);
      lcd.print("Led off");
    }
  }
  
  else{
    digitalWrite(8,LOW);
    lcd.setCursor(0,2);
    lcd.print("Manual");
    if(lamp==1){
      digitalWrite(9,HIGH);
      lcd.setCursor(0,3);
      lcd.print("lamp on ");
    }
    else{
      digitalWrite(9,LOW);
      lcd.setCursor(0,3);
      lcd.print("lamp off");
    }

    if(fan==1){
      digitalWrite(10,HIGH);
      lcd.setCursor(9,3);
      lcd.print("fan on ");
    }
    else{
      digitalWrite(10,LOW);
      lcd.setCursor(9,3);
      lcd.print("fan off");
    }
    
    if(light==1){
      digitalWrite(13,HIGH);
      lcd.setCursor(9,2);
      lcd.print("LED on ");
    }
    else{
      digitalWrite(13,LOW);
      lcd.setCursor(9,2);
      lcd.print("LED off");
    }
    
  }
}

void perform_dht(){
   h=dht.readHumidity();
   t=dht.readTemperature();

  if (isnan(h) || isnan(t) ) {
    return;
  }
   
  hic = dht.computeHeatIndex(t, h, false);
  
  if(Auto==1){
    
    digitalWrite(8,HIGH);
    lcd.setCursor(0,2);
    lcd.print("Auto  ");
    if(t>=29){
      digitalWrite(10,HIGH);
      lcd.setCursor(9,3);
      lcd.print("fan on ");
    }
    else{
      digitalWrite(10,LOW);
      lcd.setCursor(9,3);
      lcd.print("fan off");
    }
    
    
    if(light==1){
      digitalWrite(13,HIGH);
      lcd.setCursor(9,2);
      lcd.print("LED on ");
    }
    else{
      digitalWrite(13,LOW);
      lcd.setCursor(9,2);
      lcd.print("LED off");
    }
  }
  
  else{
    digitalWrite(8,LOW);
    lcd.setCursor(0,2);
    lcd.print("Manual");
    if(lamp==1){
      digitalWrite(9,HIGH);
      lcd.setCursor(0,3);
      lcd.print("lamp on ");
    }
    else{
      digitalWrite(9,LOW);
      lcd.setCursor(0,3);
      lcd.print("lamp off");
    }

    if(fan==1){
      digitalWrite(10,HIGH);
      lcd.setCursor(9,3);
      lcd.print("fan on ");
    }
    else{
      digitalWrite(10,LOW);
      lcd.setCursor(9,3);
      lcd.print("fan off");
    }
    
    if(light==1){
      digitalWrite(13,HIGH);
      lcd.setCursor(9,2);
      lcd.print("LED on ");
    }
    else{
      digitalWrite(13,LOW);
      lcd.setCursor(9,2);
      lcd.print("LED off");
    }
    
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Tem:");
  lcd.print(t);
  lcd.print("C ");
  lcd.print("Hu:");
  lcd.print(h);
  lcd.print("%");
  
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print("\n");
  
}

void receive_json(){
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);

    if (root == JsonObject::invalid())
    {
      return;
    }


  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Automate: ");
  Auto=root["LED1"];
  Serial.println(Auto);
  Serial.print("Lamp:   ");
  lamp=root["LED2"];
  Serial.println(lamp);
  Serial.print("Fan:  ");
  fan=root["LED3"];
  Serial.println(fan);
  Serial.print("light  ");
  light=root["LED4"];
  Serial.println(light);
  Serial.println("---------------------xxxxx--------------------");
  Serial.println("");
}
