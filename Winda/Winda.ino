#include <Stepper.h>
#include <LiquidCrystal.h>

// Piny przycisków
#define przycisk_pietro1 1
#define przycisk_pietro2 12
#define przycisk_pietro3 13

// Piny czujników pięter
#define czujnik_pietro1 A0
#define czujnik_pietro2 A1
#define czujnik_pietro3 A2

// Silnik krokowy i wyświetlacz
const int kroki_na_obrot = 2048;
Stepper silnik(kroki_na_obrot, 8, 10, 9, 11);
LiquidCrystal ekran(2, 3, 4, 5, 6, 7);

// Zmienne windy
int aktualne_pietro = 1;
int offset = 2500;
const int MAKS_ZADAN = 10;
int kolejka[MAKS_ZADAN];
int liczba_zadan = 0;

// Tablice pomocnicze
int przyciski[4];  
int czujniki[4];
bool pietro_obsluzone[4];

// Debounce
unsigned long ostatni_czas_przycisku[4];
const unsigned long opoznienie_przycisku = 200;

// Stany czujników
bool poprzedni_stan_czujnika[4];

// Dodaj piętro do kolejki
void dodaj_pietro(int pietro) {
  if (pietro < 1 || pietro > 3) return;
  for (int i = 0; i < liczba_zadan; i++) if (kolejka[i] == pietro) return;
  if (liczba_zadan < MAKS_ZADAN) kolejka[liczba_zadan++] = pietro;
}

// Usuń pierwsze wystąpienie piętra z kolejki
void usun_pietro_z_kolejki(int pietro) {
  bool usunieto = false;
  int zapis = 0;
  for (int odczyt = 0; odczyt < liczba_zadan; odczyt++) {
    if (!usunieto && kolejka[odczyt] == pietro) { 
      usunieto = true; 
      continue; 
    }
    kolejka[zapis++] = kolejka[odczyt];
  }
  liczba_zadan = zapis;
}

// Sprawdzenie przycisków
void sprawdz_przyciski() {
  unsigned long teraz = millis();
  for (int p = 1; p <= 3; p++) {
    if (digitalRead(przyciski[p]) == LOW && teraz - ostatni_czas_przycisku[p] > opoznienie_przycisku) {
      dodaj_pietro(p);
      ostatni_czas_przycisku[p] = teraz;
    }
  }
}

// Obsługa przyjazdu na piętro
void obsluz_przyjazd(int pietro, int kierunek) {
  usun_pietro_z_kolejki(pietro);
  pietro_obsluzone[pietro] = true;

  ekran.clear();
  ekran.setCursor(0,0);
  ekran.print("Winda na pietrze:");
  ekran.setCursor(0,1);
  ekran.print(pietro);

  if (pietro == 2) {
    for (int i = 0; i < offset; i++) silnik.step(kierunek);
    poprzedni_stan_czujnika[2] = (digitalRead(czujniki[2]) == LOW);
  }

  aktualne_pietro = pietro;

  unsigned long start = millis();
  while (millis() - start < 3000) {
    sprawdz_przyciski();
    delay(10);
  }
}

// Wybierz najbliższe nieobsłużone piętro z kolejki
int wybierz_nastepne_pietro() {
  int min_odleglosc = 100;
  int nastepne = 0;
  for (int i = 0; i < liczba_zadan; i++) {
    int pietro = kolejka[i];
    if (!pietro_obsluzone[pietro]) {
      int odleglosc = abs(pietro - aktualne_pietro);
      if (odleglosc < min_odleglosc) {
        min_odleglosc = odleglosc;
        nastepne = pietro;
      }
    }
  }
  return nastepne;
}

// Ruch windy
void jedz_do_pietra() {
  for (int i = 1; i <= 3; i++) pietro_obsluzone[i] = false;

  while (liczba_zadan > 0) {
    int nastepne = wybierz_nastepne_pietro();
    if (nastepne == 0) break;

    int kierunek = (nastepne > aktualne_pietro) ? 1 : -1;

    // Wyświetl informację na LCD przed ruszeniem
    ekran.clear();
    ekran.setCursor(0,0);
    ekran.print("Jedzie na pietro:");
    ekran.setCursor(0,1);
    ekran.print(nastepne);

    bool dotarl = false;

    while (!dotarl) {
      silnik.step(kierunek);
      sprawdz_przyciski();

      for (int f = 1; f <= 3; f++) {
        bool teraz = (digitalRead(czujniki[f]) == LOW);
        if (teraz && !poprzedni_stan_czujnika[f] && !pietro_obsluzone[f]) {
          obsluz_przyjazd(f, kierunek);
          if (f == nastepne) dotarl = true;
        }
        poprzedni_stan_czujnika[f] = teraz;
      }
    }
  }
}


void setup() {
  silnik.setSpeed(10);
  przyciski[1] = przycisk_pietro1; przyciski[2] = przycisk_pietro2; przyciski[3] = przycisk_pietro3;
  czujniki[1] = czujnik_pietro1; czujniki[2] = czujnik_pietro2; czujniki[3] = czujnik_pietro3;

  for (int i = 1; i <=3; i++) {
    pinMode(przyciski[i], INPUT_PULLUP);
    pinMode(czujniki[i], INPUT_PULLUP);
    poprzedni_stan_czujnika[i] = (digitalRead(czujniki[i]) == LOW);
  }

  ekran.begin(16,2);
  ekran.print("Start windy...");
  aktualne_pietro = 1; // domyślnie start na 1 piętrze
}

void loop() {
  sprawdz_przyciski();
  if (liczba_zadan > 0) jedz_do_pietra();
  delay(5);
}
