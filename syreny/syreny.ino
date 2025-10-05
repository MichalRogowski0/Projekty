#include <Adafruit_NeoPixel.h> 

Adafruit_NeoPixel linijka = Adafruit_NeoPixel(8, A0, NEO_GRB + NEO_KHZ800);
int czas = 0; 

void setup() {

  linijka.begin(); 
  linijka.show();
  pinMode(3, OUTPUT);
}

void loop() {

  for(int wypelnienie = 600; wypelnienie <= 1200; wypelnienie += 20){

    tone(3, wypelnienie);
    swiatla(0);
    delay(30);
  }

  for(int wypelnienie = 1200; wypelnienie >= 600 ; wypelnienie -= 20){

    tone(3, wypelnienie);
    swiatla(1);
    delay(30);

    
  }
}

void swiatla(int strona){

    if (strona == 0) {
      linijka.setPixelColor(0, linijka.Color(0, 0, 255));
      linijka.setPixelColor(1, linijka.Color(0, 0, 255));
      linijka.setPixelColor(2, linijka.Color(0, 0, 255));
      linijka.setPixelColor(5, 0);
      linijka.setPixelColor(6, 0);
      linijka.setPixelColor(7, 0);
  } 
  else {
      linijka.setPixelColor(5, linijka.Color(0, 0, 255));
      linijka.setPixelColor(6, linijka.Color(0, 0, 255));
      linijka.setPixelColor(7, linijka.Color(0, 0, 255));
      linijka.setPixelColor(0, 0);
      linijka.setPixelColor(1, 0);
      linijka.setPixelColor(2, 0);
  }


  linijka.setPixelColor(3, linijka.Color(255, 255, 255)); 
  linijka.setPixelColor(4, linijka.Color(255, 0, 0));     

  linijka.show();

}