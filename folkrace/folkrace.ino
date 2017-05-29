#include <NewPing.h>
#define TRIGGER_PIN 8
#define ECHO_PIN 7
#define MAX_DISTANCE 100
#define RF 5
#define RB 6
#define LF 11
#define LB 10
#define IRS A0
#define MAX_FORWARD 200
#define TURNING 125

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(IRS, INPUT);
}

int getIRSensorCM(int mv)
{
  /*float volts = mv*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
  return distance/100;*/
  return (2914/(mv+5))-1;
}

void loop() {
  //analogWrite(LF, 75);
  //analogWrite(RF, 75);
  delay(75);
  unsigned int uS = sonar.ping();
  int distance = sonar.convert_cm(uS);
  int distance2 = getIRSensorCM(analogRead(IRS));
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.println("cm");
  
  if((distance > 0 && distance < 20) || (distance2 < 20)) //Something is in my way! Get rid of it!
  {
    if(distance >= distance2) //Vasak on kaugemal
    {
      analogWrite(RF, TURNING);
      analogWrite(RB, 0);
      analogWrite(LF, 0);
      analogWrite(LB, TURNING);
    }
    else if(distance < distance2) //Parem on kaugemal
    {
      analogWrite(RF, 0);
      analogWrite(RB, TURNING);
      analogWrite(LF, TURNING);
      analogWrite(LB, 0);
    }
    /*analogWrite(RB, 0);
    analogWrite(RF, TURNING);
    analogWrite(LB, TURNING);
    analogWrite(LF, 0);*/
    delay(75);
  }
  else
  {
    analogWrite(RF, MAX_FORWARD);
    analogWrite(RB, 0);
    analogWrite(LF, MAX_FORWARD);
    analogWrite(LB, 0);
  }
}
