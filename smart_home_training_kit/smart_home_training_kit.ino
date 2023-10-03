/*
LIST OF LIBRARIES USED
*/

#include <SPI.h>
#include <MFRC522.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>


/*
 * 
 * ALL THE PINOUT CAN BE CHANGED TO TO CONNECTIONS
 * 
 */

//LED PINOUT
#define led_1 49 //dining room
#define led_2 48 //kitchen
#define led_3 47 //living room
#define led_4 46 //master bedroom
#define led_5 45 //bedroom 1
#define led_6 44 //bedroom 2
#define led_7 43 // bedroom 3
#define led_8 42 //toilet 1
#define led_9 41 //toilet 2
#define led_10 40 //garage
#define rgb_r1 39 //rgb 1 red
#define rgb_g1 38 //rgb 1 green
#define rgb_b1 37 //rgb 1 blue
#define rgb_r2 36 //rgb 2 red
#define rgb_g2 35 //rgb 2 green
#define rgb_b2 34 //rgb 2 blue
#define fan_red 33
#define fan_yellow 32
#define fan_green 31
#define led12 30 //led green surveillence
#define led13 29 //led red surveillence

//SENSOR PINOUT
#define gas A0
#define smoke A1
#define rain A2
#define ldr A3
#define touch_1 3
#define touch_2 4
#define motion_sensor 28 //can be change
#define DHTPIN 2 //pinout can be change

//PUSH BUTTON PINOUT
#define s1 20
#define s2 21
#define s3 22
#define s4 23
#define s5 24
#define s6 25

//MOTOR DRIVER PINOUT
#define ena 6
#define in1 7
#define in2 8
#define enb 9
#define in3 10
#define in4 11

//OTHERS PINOUT
#define BUZZER 26 //buzzer pin
#define RELAY 27 //relay pin
#define servo_pin 12 //pin servo 
#define servo1_pin 13 //pin servo 1

//LCD PINOUT
#define rs 19
#define en 18
#define d4 17
#define d5 16
#define d6 15
#define d7 14


/*
 * * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * 
 * 
 */
 
//rfid settings
#define SS_PIN 53
#define RST_PIN 5
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.



//dht sensor settings
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

//motion sensor settings
int motion_state = LOW;

//lcd settings
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

//push button settings
int state1 = false;
int state2 = false;
int state3 = false;
int state4 = false;
int state5 = false;
int state6 = false;
int state_touch1 = false;
int state_touch2 = false;

int lastButtonState_s1; 
int lastButtonState_s2; 
int lastButtonState_s3; 
int lastButtonState_s4; 
int lastButtonState_s5; 
int lastButtonState_s6; 
int lastButtonState_t1;
int lastButtonState_t2;   
int currentButtonState_s1; 
int currentButtonState_s2; 
int currentButtonState_s3; 
int currentButtonState_s4; 
int currentButtonState_s5; 
int currentButtonState_s6; 
int currentButtonState_t1; 
int currentButtonState_t2;

//servo settings
Servo servo1;
Servo servo2;


void setup() {

  Serial.begin(9600);

  //pinmode output
  pinMode(led_1,OUTPUT);
  pinMode(led_2,OUTPUT);
  pinMode(led_3,OUTPUT);
  pinMode(led_4,OUTPUT);
  pinMode(led_5,OUTPUT);
  pinMode(led_6,OUTPUT);
  pinMode(led_7,OUTPUT);
  pinMode(led_8,OUTPUT);
  pinMode(led_9,OUTPUT);
  pinMode(led_10,OUTPUT);
  pinMode(rgb_r1,OUTPUT);
  pinMode(rgb_g1,OUTPUT);
  pinMode(rgb_b1,OUTPUT);
  pinMode(rgb_r2,OUTPUT);
  pinMode(rgb_g2,OUTPUT);
  pinMode(rgb_b2,OUTPUT);
  pinMode(fan_red,OUTPUT);
  pinMode(fan_yellow,OUTPUT);
  pinMode(fan_green,OUTPUT);
  pinMode(led12,OUTPUT);
  pinMode(led13,OUTPUT);

  //other
  pinMode(RELAY,OUTPUT);
  pinMode(BUZZER,OUTPUT);

  //servo
  servo1.attach(servo_pin);
  servo2.attach(servo1_pin);

  //sensor
  pinMode(touch_1,INPUT);
  pinMode(touch_2,INPUT);
  pinMode(motion_sensor, INPUT);

  //push button
  pinMode(s1,INPUT_PULLUP);
  pinMode(s2,INPUT_PULLUP);
  pinMode(s3,INPUT_PULLUP);
  pinMode(s4,INPUT_PULLUP);
  pinMode(s5,INPUT_PULLUP);
  pinMode(s6,INPUT_PULLUP);

  //motor driver
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);

  //rfid
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  //dht
  dht.begin();

  //lcd
  lcd.begin(16,2); 

  //initial state led
  digitalWrite(led_1,LOW);
  digitalWrite(led_2,LOW);
  digitalWrite(led_3,LOW);
  digitalWrite(led_4,LOW);
  digitalWrite(led_5,LOW);
  digitalWrite(led_6,LOW);
  digitalWrite(led_7,LOW);
  digitalWrite(led_8,LOW);
  digitalWrite(led_9,LOW);
  digitalWrite(led_10,LOW);
  digitalWrite(rgb_r1,LOW);
  digitalWrite(rgb_g1,LOW);
  digitalWrite(rgb_b1,LOW);
  digitalWrite(rgb_r2,LOW);
  digitalWrite(rgb_g2,LOW);
  digitalWrite(rgb_b2,LOW);
  digitalWrite(fan_red,LOW);
  digitalWrite(fan_yellow,LOW);
  digitalWrite(fan_green,LOW);
  digitalWrite(led12,LOW);
  digitalWrite(led13,LOW);

}

void loop() {

  //sensor
  int read_rain = analogRead(rain);
  int read_gas = analogRead(gas);
  int read_smoke = analogRead(smoke);
  int read_ldr = analogRead(ldr);
  int motion_val = digitalRead(motion_sensor);

  //switches
  lastButtonState_t1    = currentButtonState_t1;
  lastButtonState_t2    = currentButtonState_t2;
  lastButtonState_s1    = currentButtonState_s1;
  lastButtonState_s2    = currentButtonState_s2;
  lastButtonState_s3    = currentButtonState_s3;
  lastButtonState_s4    = currentButtonState_s4;
  lastButtonState_s5    = currentButtonState_s5;
  lastButtonState_s6    = currentButtonState_s6; 
  currentButtonState_t1 = digitalRead(touch_1);
  currentButtonState_t1 = digitalRead(touch_2);
  currentButtonState_s1 = digitalRead(s1);
  currentButtonState_s2 = digitalRead(s2);
  currentButtonState_s3 = digitalRead(s3);
  currentButtonState_s4 = digitalRead(s4);
  currentButtonState_s5 = digitalRead(s5);
  currentButtonState_s6 = digitalRead(s6);

  //dht
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  /*
   * 
   * FLOWS
   * 
   */

   
   //Serial.println("Temperature:" + String(t));
   //Serial.println("Humidity:" + String(h));
   lcd.setCursor(0,0);
   lcd.print("Temperature : " + String(t)+"C");
   lcd.setCursor(0,1);
   lcd.print("Humidity : " + String(h)+"%");
  
  
   read_rfid();
      
   if(read_gas > 500){
  Serial.println("Gas value :" + String(read_gas));
  digitalWrite(BUZZER, HIGH);
  delay(3000);
  }
   if(read_smoke > 500){
  Serial.println("Smoke value :" + String(read_smoke));
  digitalWrite(BUZZER, HIGH);
  delay(3000);
  }
  if(read_ldr < 5){
  Serial.println("LDR value :" + String(read_ldr));
  digitalWrite(led_10, HIGH);
  delay(3000);
  }
  if(read_rain < 600){
  Serial.println("Rain value :" + String(read_rain));
  servo1.write(0);
  delay(3000);
  }
  if(lastButtonState_s1 == LOW && currentButtonState_s1 == HIGH){
  state1 = !state1;
  digitalWrite(led_1,state1); 
  }
  if(lastButtonState_t1 == LOW && currentButtonState_t1 == HIGH){
  state1 = !state1;
  digitalWrite(led_2,state1); 
  }
  if(t>36){
    analogWrite(ena,255);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    delay(5000);
  }
  if (motion_val == HIGH) {           
    digitalWrite(led13, HIGH);  
    digitalWrite(BUZZER, HIGH);
    delay(100);               
    
    if (motion_state == LOW) {
      Serial.println("Motion detected!"); 
      motion_state = HIGH;      
    }
  } 



  
     else{
     analogWrite(ena,0);
     digitalWrite(in1,LOW);
     digitalWrite(in2,LOW);
     digitalWrite(BUZZER, LOW);
     digitalWrite(led_10, LOW);
     digitalWrite(led13, HIGH);
     servo1.write(90);//buka tingkap
     if (motion_state == HIGH){
      Serial.println("Motion stopped!");
      motion_state = LOW;}

    }
    delay(1000);

    

    
}

void read_rfid(){
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "D3 87 BE 2E") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    servo2.write(90);
    digitalWrite(RELAY,HIGH);
    delay(5000);
    digitalWrite(RELAY,LOW);
    servo2.write(0);
  }
  else{
    digitalWrite(RELAY,LOW);
    servo2.write(00);
  }
    // Halt PICC
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
  
}
