#include<Servo.h>
Servo udServo;
static int upDown=10;
char buffer_value;
int servoPin=2, lPower=9, rPower=10, mDL1=34, mDL2=35, mDR1=36, mDR2=37;
void setup() {
  Serial.begin(19200);
  Serial1.begin(9600);
  pinMode(servoPin, OUTPUT);
  udServo.attach(servoPin);
  udServo.write(10);
}

void servoUp(int power)
{
  if(upDown<=100)
    upDown+=power;
  if(upDown>100)
    upDown=100;
  udServo.write(upDown);
}

void servoDown(int power)
{
  if(upDown>=10)
    upDown-=power;
  if(upDown<10)
    upDown=10;
  udServo.write(upDown);
}

void motorDriverSetup()
{
  pinMode(lPower, OUTPUT);
  pinMode(rPower, OUTPUT);
  pinMode(mDL1, OUTPUT);
  pinMode(mDL2, OUTPUT);
  pinMode(mDR1, OUTPUT);
  pinMode(mDR2, OUTPUT);
}

void forward(int power)
{
  analogWrite(lPower,power);
  analogWrite(rPower,power);
  digitalWrite(mDL1,LOW);
  digitalWrite(mDL2,HIGH);
  digitalWrite(mDR1,LOW);
  digitalWrite(mDR2,HIGH);
}

void backward(int power)
{
  analogWrite(lPower,power);
  analogWrite(rPower,power);
  digitalWrite(mDL1,HIGH);
  digitalWrite(mDL2,LOW);
  digitalWrite(mDR1,HIGH);
  digitalWrite(mDR2,LOW);
}

void right(int power)
{
  analogWrite(lPower,power);
  analogWrite(rPower,power);
  digitalWrite(mDL1,LOW);
  digitalWrite(mDL2,HIGH);
  digitalWrite(mDR1,HIGH);
  digitalWrite(mDR2,LOW);
}

void left(int power)
{
  analogWrite(lPower,power);
  analogWrite(rPower,power);
  digitalWrite(mDL1,HIGH);
  digitalWrite(mDL2,LOW);
  digitalWrite(mDR1,LOW);
  digitalWrite(mDR2,HIGH);
}

void stopMoving()
{
  analogWrite(lPower,0);
  analogWrite(rPower,0);
  digitalWrite(mDL1,LOW);
  digitalWrite(mDL2,LOW);
  digitalWrite(mDR1,LOW);
  digitalWrite(mDR2,LOW);
}

void bodyCheck()
{
  left(100);
  delay(300);
  right(100);
  delay(600);
  left(100);
  delay(300);
  stopMoving();
  for(int i=10; i<=40; i+=1){
    delay(2);
    udServo.write(i);
  }
}

void loop() {
  if(Serial1.available()>0)
  {
    buffer_value = Serial1.read();
    Serial.print("value is:");
    Serial.println(buffer_value);
    switch(buffer_value){
      case 'p':
        stopMoving();
      break;
      case 'c':
        bodyCheck();
      break;
      case 'r':
        right(90);
      break;
      case 'R':
        right(120);
      break;
      case 'l':
        left(87);
      break;
      case 'L':
        left(120);
      break;
      case 'u':
        servoUp(4);
      break;
      case 'U':
        servoUp(7);
      break;
      case 'd':
        servoDown(4);
      break;
      case 'D':
        servoDown(7);
      break;
      case 'f':
        forward(100);
      break;
      case 'F':
        forward(180);
      break;
      case 'b':
        backward(100);
      break;
      case 'B':
        backward(180);
      break;
      default:
        stopMoving();
      break;
    }
  }
}
