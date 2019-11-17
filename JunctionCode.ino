#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4
#define outputA 11
#define outputB 12 


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo myservo;
Servo Servo1;

unsigned long currentTime;
bool victory=true;

const String mpf = "Perfect Passeword";
const String mpb = "Medium Passeword";
const String mptf1 = "Verry bad";
const String mptf2 = "passeword";
const String welcome = "Welcome";
const String wait1 = "Waiting for the";
const String wait2 = "Passeword :D";

String lifeStr = "";

char data;

byte count=0;
byte life=0;

int counter = 0; 
int aState;
int aLastState;
bool hd1,hd2;


void setup() {
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(9,OUTPUT);
digitalWrite(2,LOW);
digitalWrite(3,LOW);
digitalWrite(9,LOW);

pinMode(7,INPUT);
pinMode(8,OUTPUT);
digitalWrite(8,LOW);
life = 100;
Servo1.attach(3);  
myservo.attach(6);
pinMode(4,INPUT);
pinMode(13,OUTPUT); 
Servo1.write(1);
delay(40);
myservo.write(180);
delay(40);
Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
display.clearDisplay();


pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   aLastState = digitalRead(outputA);   
   delay(40);
   hd1=hd2=false;
}

void loop() {
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
while(true){
afficherWait();
if (Serial.available()){
  data = Serial.read();
  Serial.println(data);
  if (data == '1' ){  //Dans le cas ou le mot de passe est fort
    clearLCD();
    afficherMPF();
    delay(5000);
    myservo.write(5);
    clearLCD();
    display.display();
    break;
  }
  
  else if (data == '2' ){  //Dans le cas ou le mot de passe est un peu faible
    clearLCD();
    afficherMPB();
    delay(5000);
    clearLCD();
    display.display();
  }
  
  else if (data == '3' ){  //Dans le cas ou le mot de passe est très fabile faible
    clearLCD();
    afficherMPTF();
    delay(5000);
    clearLCD();
    display.display();
  }  
 }
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
while(true){
 currentTime=millis();  
 while (millis()-currentTime < 7000){
   if(!digitalRead(4)) {Servo1.write(110),delay(40);victory=false;afficherLose();delay(4000);display.clearDisplay();break;}
  } 
 if(victory==true){
 afficheGJ();delay(4000);display.clearDisplay();Blinky(10,400);break;
 }
 break;
 }  
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
life = 3;
while(true){
 if (digitalRead(7)) {digitalWrite(8,HIGH);count++;}
 else digitalWrite(8,LOW);
 //afficher sur LCD combiens de vie il reste
 if (count > 2) {life--;count = 0;}
 Serial.print("Life= ");Serial.println(life);
 if (life == 0) {afficheDead();delay(4000);display.clearDisplay();break;}
 lifeStr = String(life);
 afficherVie(lifeStr);
 delay(300);
 }
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

while (true){
  aState = digitalRead(outputA);   
   if (aState != aLastState){     
   if (digitalRead(outputB) != aState) { 
       counter ++;
     } 
   else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState;

  
  if (counter>-20) { 

    while(true){
      violet();delay(1000);orange();delay(1000);
      }
   
    }
  
  }

}

void afficher(String y){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);    
display.setCursor(5,15);                  
display.println(y); 
display.display();
  }

void afficherMPF(){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);    
display.setCursor(5,15);                  
display.println(mpf); 
display.display();
  }

void afficherMPB(){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);    
display.setCursor(5,15);                  
display.println(mpb); 
display.display();
  }

void afficherMPTF(){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);    
display.setCursor(30,7);                  
display.println(mptf1); 
display.setCursor(30,24);
display.println(mptf2);
display.display();
  }

void afficherWait(){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);    
display.setCursor(25,7);                  
display.println(wait1); 
display.setCursor(25,24);
display.println(wait2);
display.display();
  }

void afficherWelcome(){
display.clearDisplay();
display.setTextSize(2);                    
display.setTextColor(WHITE);
display.setCursor(10,17);
display.println(welcome);
display.display();
  }

void afficherVie(String x){
display.clearDisplay();
display.setTextSize(2);                    
display.setTextColor(WHITE);
display.setCursor(10,17);
display.println("LIFE =  ");
display.setCursor(95,17);
display.println(lifeStr);
display.display();
  }

void afficherLose(){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);
display.setCursor(20,17);
display.println("Don't Give");
display.setCursor(10,24);
display.println("your passeword");
display.display();
  }

void afficheGJ(){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);
display.setCursor(10,24);
display.println("Good Job !!");
display.display();  
  }

void afficheDead(){
display.clearDisplay();
display.setTextSize(1);                    
display.setTextColor(WHITE);
display.setCursor(10,24);
display.println("Ouuups!!");
display.display();  
  }
 

void clearLCD(){
  display.clearDisplay();
  }



void Blinky(int i, int t){
  for(i=0;i<10;i++){
    digitalWrite(13,LOW);delay(t);digitalWrite(13,HIGH);delay(t);
    }
    digitalWrite(13,LOW);
  }  

  
 void violet(){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(9,LOW);
  }

  void orange(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(9,HIGH);
  }
