#include <Stepper.h>
#include <LiquidCrystal.h>

#define P1_PRZYCISK 1
#define P2_PRZYCISK 12
#define P3_PRZYCISK 13

#define P1_CZUJNIK A0
#define P2_CZUJNIK A1
#define P3_CZUJNIK A2

#define ILOSC_KROKOW 2048
#define DOJEDZ 2500
#define MAX_KOLEJKA 10

int kolejka[MAX_KOLEJKA];
int ilosc = 0;
int poczatek = 0;
int koniec = 0;

Stepper silnik(ILOSC_KROKOW, 8, 10, 9, 11);
LiquidCrystal lcd(2,3,4,5,6,7);

// -------- KOLEJKA --------
void dodaj_do_kolejki(int pietro){
  if(ilosc < MAX_KOLEJKA){
    kolejka[koniec] = pietro;
    koniec = (koniec+1)%MAX_KOLEJKA;
    ilosc++;
  }
}

void usun_z_kolejki(int pietro){
  for(int i=0;i<ilosc;i++){
    int idx = (poczatek+i)%MAX_KOLEJKA;
    if(kolejka[idx]==pietro){
      for(int j=i;j<ilosc-1;j++){
        int nextIdx = (poczatek+j+1)%MAX_KOLEJKA;
        kolejka[(poczatek+j)%MAX_KOLEJKA] = kolejka[nextIdx];
      }
      ilosc--;
      koniec = (koniec-1+MAX_KOLEJKA)%MAX_KOLEJKA;
      return;
    }
  }
}

bool jest_w_kolejce(int pietro){
  for(int i=0;i<ilosc;i++){
    int idx = (poczatek+i)%MAX_KOLEJKA;
    if(kolejka[idx]==pietro) return true;
  }
  return false;
}

int odczytaj_z_kolejki(){
  if(ilosc > 0){
    int pietro = kolejka[poczatek];
    poczatek = (poczatek+1)%MAX_KOLEJKA;
    ilosc--;
    return pietro;
  }
  return -1;
}

// -------- SPRAWDZANIE PRZYCISKÓW --------
void sprawdz_przyciski(){
  if(digitalRead(P1_PRZYCISK)==LOW){ dodaj_do_kolejki(1); delay(200); }
  if(digitalRead(P2_PRZYCISK)==LOW){ dodaj_do_kolejki(2); delay(200); }
  if(digitalRead(P3_PRZYCISK)==LOW){ dodaj_do_kolejki(3); delay(200); }
}

// -------- JAZDA WINDY --------
void jedz_do_pietra(int cel){
  lcd.clear();
  lcd.print("Jedzie na ");
  lcd.print(cel);

  int kierunek = 0;
  if(cel==1) kierunek=-1;
  if(cel==3) kierunek=1;
  if(cel==2){
    if(digitalRead(P1_CZUJNIK)==LOW) kierunek=1;
    else if(digitalRead(P3_CZUJNIK)==LOW) kierunek=-1;
    else kierunek=1; // start z 2 -> w górę
  }

  if(cel==1){
    while(digitalRead(P1_CZUJNIK)==HIGH){
      silnik.step(kierunek);
      sprawdz_przyciski();
      // DOJEDZ na 2 piętro w trakcie jazdy
      if(jest_w_kolejce(2) && digitalRead(P2_CZUJNIK)==LOW){
        silnik.step(-DOJEDZ);
        lcd.clear(); lcd.print("Drugie pietro");
        usun_z_kolejki(2);
        delay(3000);
      }
    }
    lcd.clear(); lcd.print("Pierwsze pietro");
    delay(3000);
  }

  if(cel==2){
    while(digitalRead(P2_CZUJNIK)==HIGH){
      silnik.step(kierunek);
      sprawdz_przyciski();
    }
    silnik.step(kierunek*DOJEDZ);
    lcd.clear(); lcd.print("Drugie pietro");
    delay(3000);
    usun_z_kolejki(2);
  }

  if(cel==3){
    while(digitalRead(P3_CZUJNIK)==HIGH){
      silnik.step(kierunek);
      sprawdz_przyciski();
      if(jest_w_kolejce(2) && digitalRead(P2_CZUJNIK)==LOW){
        silnik.step(DOJEDZ);
        lcd.clear(); lcd.print("Drugie pietro");
        usun_z_kolejki(2);
        delay(3000);
      }
    }
    lcd.clear(); lcd.print("Trzecie pietro");
    delay(3000);
  }
}

// -------- SETUP --------
void setup(){
  silnik.setSpeed(15);

  pinMode(P1_PRZYCISK, INPUT_PULLUP);
  pinMode(P2_PRZYCISK, INPUT_PULLUP);
  pinMode(P3_PRZYCISK, INPUT_PULLUP);

  pinMode(P1_CZUJNIK, INPUT_PULLUP);
  pinMode(P2_CZUJNIK, INPUT_PULLUP);
  pinMode(P3_CZUJNIK, INPUT_PULLUP);

  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Winda gotowa");
  delay(1500);
}

// -------- LOOP --------
void loop(){
  sprawdz_przyciski();
  if(ilosc>0){
    int cel = odczytaj_z_kolejki();
    if(cel!=-1) jedz_do_pietra(cel);
  }
}
