#include<NewPing.h>
#include<Servo.h>
#include<AFMotor.h>
#define RIGHT A2
#define LEFT A3
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 100
NewPing utsensor(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);
AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);
Servo utservo;
int servpos=0;
void setup(){
  Serial.begin(9600);
  utservo.attach(10);
  {
    for(servpos=90;servpos<=180;servpos+=1){
      utservo.write(servpos);
      delay(15);
    }
    for(servpos=180;servpos>=0;servpos-=1){
      utservo.write(servpos);
      delay(15);
    }
    for(servpos=0;servpos<=90;servpos+=1){
      utservo.write(servpos);
      delay(15);
    }
  }
  pinMode(RIGHT,INPUT);
  pinMode(LEFT,INPUT);
}
void loop() {
  delay(50);
  unsigned int hmS=utsensor.ping_cm();
  Serial.print("Distance From Human: ");
  Serial.println(hmS);
  int RIrVal=digitalRead(RIGHT);
  int LIrVal=digitalRead(LEFT);
  Serial.print("RIGHT");
  Serial.println(RIrVal);
  Serial.print("LEFT");
  Serial.println(LIrVal);
  if((RIrVal==1)&&(hmS>=10&&hmS<=30)&&(LIrVal==1)){
    Motor1.setSpeed(120);
    Motor1.run(FORWARD);
    Motor2.setSpeed(120);
    Motor2.run(FORWARD);
    Motor3.setSpeed(120);
    Motor3.run(FORWARD);
    Motor4.setSpeed(120);
    Motor4.run(FORWARD);
  }
  else if((RIrVal==0)&&(LIrVal==1)){
    Motor1.setSpeed(200);
    Motor1.run(FORWARD);
    Motor2.setSpeed(200);
    Motor2.run(FORWARD);
    Motor3.setSpeed(100);
    Motor3.run(BACKWARD);
    Motor4.setSpeed(100);
    Motor4.run(BACKWARD);
  }
  else if((RIrVal==1)&&(LIrVal==0)){
    Motor1.setSpeed(100);
    Motor1.run(BACKWARD);
    Motor2.setSpeed(100);
    Motor2.run(BACKWARD);
    Motor3.setSpeed(200);
    Motor3.run(FORWARD);
    Motor4.setSpeed(200);
    Motor4.run(FORWARD);
  }
  else if((RIrVal==1)&&(LIrVal==1)){
    Motor1.setSpeed(0);
    Motor1.run(RELEASE);
    Motor2.setSpeed(0);
    Motor2.run(RELEASE);
    Motor3.setSpeed(0);
    Motor3.run(RELEASE);
    Motor4.setSpeed(0);
    Motor4.run(RELEASE);
  }
  else if(hmS>1&&hmS<10){
    Motor1.setSpeed(0);
    Motor1.run(RELEASE);
    Motor2.setSpeed(0);
    Motor2.run(RELEASE);
    Motor3.setSpeed(0);
    Motor3.run(RELEASE);
    Motor4.setSpeed(0);
    Motor4.run(RELEASE);
  }
}
