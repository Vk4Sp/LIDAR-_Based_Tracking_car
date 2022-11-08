#include <AFMotor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
#include <SoftwareSerial.h>
SoftwareSerial Serial1(2,3);
int dist;
int strength;
int check;
int uart[9];
int i;
const int HEADER=0x59;
void setup(){
    Serial.begin(115200);
    Serial1.begin(115200);
    motor1.setSpeed(200);
    motor2.setSpeed(200);
    motor3.setSpeed(200);        
    motor4.setSpeed(200);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);              
}
void loop()
{
  if(Serial1.available())
  {
    if(Serial1.read()==HEADER)
    {
      uart[0]=HEADER;
      if(Serial1.read()==HEADER)
      {
        uart[1]=HEADER;
        for(i=2;i<9;i++)
        {
          uart[i]=Serial1.read(); 
        } 
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        if(uart[8]==(check&0xff))
        {
          dist = uart[2]+uart[3]*256;
          strength = uart[4]+uart[5]*256;
if (dist==25){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(300);  }
else if(dist>=25){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);  
}
else if(dist<=25){ 
    motor1.run(BACKWARD);  
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);           
        }                            
        }
      }
    }
  }
}
