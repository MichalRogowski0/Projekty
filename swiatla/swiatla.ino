#define czerwona 8
#define zolta 9
#define zielona 10
#define echoPin 11
#define trigPin 12 

void setup() {

  Serial.begin(9600);

  pinMode(czerwona, OUTPUT);
  pinMode(zolta, OUTPUT);
  pinMode(zielona, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(czerwona, HIGH);
  digitalWrite(zolta, LOW);
  digitalWrite(zielona, LOW);
}

void loop() {

  int odleglosc = zmierzOdleglosc();
  int max_czas = 0;


  if( odleglosc < 10 ){

        for(int x = 8; x < 10; x++){

          digitalWrite(x, HIGH);
          delay(1000);
          digitalWrite(x, LOW);
          
        }
        while( odleglosc < 10 ){
          digitalWrite(zielona, HIGH);
          odleglosc = zmierzOdleglosc();
          delay(100);
          max_czas += 1;
          if(max_czas > 100){
            break;
          }
        }
        delay(1000);
        digitalWrite(zielona, LOW);

        for(int x = 10; x > 7; x--){

          digitalWrite(x, HIGH);
          delay(1000);
          digitalWrite(x, LOW);
        }
        
      digitalWrite(czerwona, HIGH);
      delay(5000);
  }
  delay(100);
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