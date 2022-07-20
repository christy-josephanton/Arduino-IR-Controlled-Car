#include "IRremote.h"

#define RECEIVER 2

//motor pinout defines
#define leftSpeed 5
#define leftDirA 3
#define leftDirB 4
#define rightSpeed 8
#define rightDirB 7
#define rightDirA 6

IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

unsigned long remote_signal=0;
unsigned long left=551492580;
unsigned long right=551525220;
unsigned long forward=551512980;
unsigned long back=551545620;
unsigned long speedcontrol=0;


void setup() {

  //IR sensor setup
  Serial.begin(9600);
  Serial.println("Start");
  irrecv.enableIRIn();

//motor setup

 
  pinMode(leftSpeed,OUTPUT);
  pinMode(leftDirA,OUTPUT);
  pinMode(leftDirB,OUTPUT);
  pinMode(rightSpeed,OUTPUT);
  pinMode(rightDirA,OUTPUT);
  pinMode(rightDirB,OUTPUT); 
  pinMode(9,INPUT_PULLUP); 

}

void loop() {
receive_signal();
move(remote_signal);
state_test();
}

void receive_signal(){
  //updates remote value only if a singal is detected
   if (irrecv.decode(&results)){
    analogWrite(A2,250);
  remote_signal=results.value;
  //Serial.println(results.value);
 
 irrecv.resume(); // receive the next value 
    delay(100);
 }
 //if not, set to zero
 else{
   //delay(50);
  analogWrite(A2,0);
  remote_signal=0;
 }
   Serial.println(remote_signal);
   delay(100);
}
void move(unsigned long remote_signal){
  if(remote_signal==right){
     analogWrite(leftSpeed,255); // enable on
      digitalWrite(leftDirA,HIGH); //one way
      digitalWrite(leftDirB,LOW);
      analogWrite(rightSpeed,255); // enable on
      digitalWrite(rightDirA,HIGH); //one way
      digitalWrite(rightDirB,LOW);
  }

  else if(remote_signal==left){
     analogWrite(leftSpeed,255); // enable on
      digitalWrite(leftDirA,LOW); //one way
      digitalWrite(leftDirB,HIGH);
      analogWrite(rightSpeed,255); // enable on
      digitalWrite(rightDirA,LOW); //one way
      digitalWrite(rightDirB,HIGH);
  }
  else if(remote_signal==forward){
     analogWrite(leftSpeed,255); // enable on
      digitalWrite(leftDirA,LOW); //one way
      digitalWrite(leftDirB,HIGH);
      analogWrite(rightSpeed,255); // enable on
      digitalWrite(rightDirA,HIGH); //one way
      digitalWrite(rightDirB,LOW);;
  }
  else if(remote_signal==back){
     analogWrite(leftSpeed,255); // enable on
      digitalWrite(leftDirA,HIGH); //one way
      digitalWrite(leftDirB,LOW);
      analogWrite(rightSpeed,255); // enable off
      digitalWrite(rightDirA,LOW); //one way
      digitalWrite(rightDirB,HIGH);
  }
  
  else {
      analogWrite(leftSpeed,0); // enable off
      analogWrite(rightSpeed,0); // enable off

  }
}

void state_test(){
  if(digitalRead(9)==HIGH){
      Serial.println("clicked");
  }
}
