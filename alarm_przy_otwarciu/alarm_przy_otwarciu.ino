#define czerwonyLED 4
#define zielonyLED 5
#define niebieskiLED 6
#define kontaktron 2        
#define buzzer A5


void setup() {
  pinMode(czerwonyLED, OUTPUT);
  pinMode(zielonyLED, OUTPUT);
  pinMode(niebieskiLED, OUTPUT);
  pinMode(kontaktron, INPUT_PULLUP);  
  pinMode(buzzer, OUTPUT);

  digitalWrite(czerwonyLED, LOW);
  digitalWrite(zielonyLED, HIGH);
  digitalWrite(niebieskiLED, LOW);

}

void loop() {

  if (digitalRead(kontaktron) == HIGH) { 
    digitalWrite(czerwonyLED, HIGH); 
    digitalWrite(zielonyLED, LOW);
    tone(buzzer, 4000);
    delay(100);
    noTone(buzzer);
    delay(100);
  } else {
    digitalWrite(czerwonyLED, LOW); 
    digitalWrite(zielonyLED, HIGH);
  }
}

