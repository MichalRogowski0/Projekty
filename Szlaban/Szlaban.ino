#include <Servo.h>
#define trigPin 12
#define echoPin 11


Servo serwomechanizm;
int zamkniete = 150;
int otwarte = 30;

void setup() 

{ 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  serwomechanizm.attach(9);
  serwomechanizm.write(zamkniete);      
} 
 
void loop() 
{  
  int odleglosc = zmierzOdleglosc();
  Serial.println(odleglosc);
  delay(100);

  if(odleglosc <= 10){
    serwomechanizm.write(otwarte);
  }
  else{
    serwomechanizm.write(zamkniete);
  }
  delay(3000);
}

int zmierzOdleglosc() {
  long czas, dystans;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;
  return dystans;
}