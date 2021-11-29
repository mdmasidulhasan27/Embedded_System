#include <IRremote.h>
///robotMode = 0 is remote Controll
///robotMode = 1 is Human Following
int robotMode=0;

int RECV_PIN = 7, sonar=3, servoM=11, pirPin=12;
int motorR1=10, motorR2=9, motorL1=6, motorL2=5;
int rIr1=2,rIr2=1,lIr1=5,lIr2=4,backIr=3;
float cm;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(motorL1,OUTPUT);
  pinMode(motorL2,OUTPUT);
  pinMode(motorR1,OUTPUT);
  pinMode(motorR2,OUTPUT);
  pinMode(pirPin,INPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(13,OUTPUT);
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  
  return pulseIn(echoPin, HIGH);
}

void leftSlow()
{
  analogWrite(motorL1,200);
  analogWrite(motorL2,0);
  analogWrite(motorR1,255);
  analogWrite(motorR2,0);
}

void rightSlow()
{
  analogWrite(motorL1,255);
  analogWrite(motorL2,0);
  analogWrite(motorR1,200);
  analogWrite(motorR2,0);
}

void leftFast()
{
  analogWrite(motorL1,0);
  analogWrite(motorL2,125);
  analogWrite(motorR1,125);
  analogWrite(motorR2,0);
}

void rightFast()
{
  analogWrite(motorL1,125);
  analogWrite(motorL2,0);
  analogWrite(motorR1,0);
  analogWrite(motorR2,125);
}

void foreword()
{
  analogWrite(motorL1,255);
  analogWrite(motorL2,0);
  analogWrite(motorR1,255);
  analogWrite(motorR2,0);
}

void backword()
{
  analogWrite(motorL1,0);
  analogWrite(motorL2,255);
  analogWrite(motorR1,0);
  analogWrite(motorR2,255);
}

void resetMotors()
{
  analogWrite(motorL1,0);
  analogWrite(motorL2,0);
  analogWrite(motorR1,0);
  analogWrite(motorR2,0);
}

void remoteControl()
{
      switch(results.value)
    {
      //Left
      case 16589023:
      leftFast();
      break;
      //Right
      case 16605343:
      rightFast();
      break;
      //foreWord
      case 16613503:
      foreword();
      break;
      //backWord
      case 16617583:
      backword();
      break;
      //stop
      case 16621663:
        resetMotors();
      break;
    }
  delay(10);
}

void humanFollow()
{
  if(digitalRead(pirPin)==HIGH){
    Serial.println("Moving Human");
  	cm = 0.01723 * readUltrasonicDistance(sonar, sonar);
  }
  Serial.println("following Human");
}

void loop() { 
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    if (results.value == 16580863){
      if(robotMode){
        robotMode=0;
        digitalWrite(13,LOW);
      }
      else {
        robotMode=1;
        digitalWrite(13,HIGH);
      }
    }
    irrecv.resume();
  }
  else
  {
    switch(robotMode)
    {
      case 0:
      	remoteControl();
      break;
      case 1:
        resetMotors();
      	humanFollow();
      break;
    }
  }
  Serial.println(analogRead(lIr1));
  delay(10);
}
