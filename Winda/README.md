Symulator windy z Arduino

Projekt przedstawia działający model windy sterowanej za pomocą silnika krokowego, czujników pięter i przycisków wyboru piętra, z wyświetlaczem LCD pokazującym aktualny stan windy.

Kod napisany został w języku C++ dla platformy Arduino z użyciem bibliotek Stepper.h i LiquidCrystal.h.

Opis działania:

Winda symuluje ruch pomiędzy trzema piętrami:

Każde piętro ma czujnik pozycji (np. krańcówkę lub fotokomórkę),

Każde piętro posiada przycisk wywołania windy,

Ruch realizowany jest przez silnik krokowy, który przemieszcza windę w górę lub w dół,

Wyświetlacz LCD 16x2 pokazuje aktualne piętro oraz komunikaty o ruchu.

Kiedy użytkownik naciśnie przycisk piętra, program:

Dodaje żądanie do kolejki (kolejka[]),

Wybiera najbliższe piętro do odwiedzenia,

Uruchamia silnik w odpowiednim kierunku,

Zatrzymuje się po wykryciu czujnika danego piętra,

Wyświetla komunikat na LCD i czeka chwilę na ewentualne nowe zgłoszenia.

Wykorzystane komponenty:
Arduino UNO - Mikrokontroler sterujący całością
Silnik krokowy 28BYJ-48 + sterownik ULN2003 - Realizuje ruch windy
Wyświetlacz LCD 16x2 (HD44780)	Pokazuje stan windy
3 przyciski - Wywołanie windy na poszczególne piętra
3 krańcówki - Określają aktualne piętro
Zasilanie 5V - Dla silnika, czujników i wyświetlacza

Struktura kodu

Główne funkcje programu:

dodaj_pietro(pietro) - Dodaje żądanie piętra do kolejki
usun_pietro_z_kolejki(pietro) - Usuwa obsłużone piętro
sprawdz_przyciski() - Odczytuje stan przycisków z debounce
obsluz_przyjazd(pietro, kierunek) - Obsługuje zatrzymanie na piętrze
wybierz_nastepne_pietro() - Wybiera najbliższe piętro z kolejki
jedz_do_pietra() - Realizuje faktyczny ruch windy

Wyświetlacz LCD

Na ekranie pojawiają się komunikaty:

Start windy... — podczas uruchamiania,

Jedzie na pietro: X — w trakcie ruchu,

Winda na pietrze: X — po dotarciu do celu.

Schemat połączeń:

Pin Arduino	Komponent		Opis
8, 9, 10, 11	Silnik krokowy		Sterowanie uzwojeniami
2–7		Wyświetlacz LCD		Sterowanie danymi i RS/E
1, 12, 13	Przyciski		Wywołanie pięter
A0, A1, A2	Czujniki		Detekcja pozycji windy