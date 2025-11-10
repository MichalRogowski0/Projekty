Symulator windy z Arduino

Model trójpoziomowej windy sterowanej mikrokontrolerem Arduino UNO.
Projekt demonstruje obsługę silnika krokowego, czujników pięter i przycisków wywołania, a także komunikację z wyświetlaczem LCD 16x2 informującym o aktualnym stanie windy.

⚙️ Opis działania

Symulator odwzorowuje działanie prawdziwej windy, poruszającej się pomiędzy trzema piętrami:

Każde piętro ma czujnik pozycji (np. krańcówkę lub fotokomórkę),

Dla każdego piętra przewidziano przycisk wywołania,

Ruch windy realizowany jest przez silnik krokowy 28BYJ-48 sterowany przez ULN2003,

Na wyświetlaczu LCD pojawiają się komunikaty o ruchu i aktualnym piętrze.

Po naciśnięciu przycisku piętra program:

Dodaje żądanie do kolejki zadań,

Wybiera najbliższe piętro do odwiedzenia,

Uruchamia silnik w odpowiednim kierunku,

Zatrzymuje windę po wykryciu czujnika danego piętra,

Wyświetla komunikat na ekranie LCD i czeka na kolejne zgłoszenia.

🧩 Wykorzystane komponenty

🧠 Arduino UNO - Sterowanie całym układem
🔁 Silnik krokowy 28BYJ-48 + ULN2003 - Ruch windy góra/dół
🖥️ Wyświetlacz LCD 16x2 (HD44780) - Pokazuje stan windy
🔘 3 przyciski - Wywołanie windy na poszczególne piętra
⚙️ 3 krańcówki - Detekcja aktualnego piętra
🔌 Zasilanie 5V	Dla silnika, czujników i LCD


🧠 Struktura kodu

Najważniejsze funkcje programu:

dodaj_pietro(pietro) – dodaje żądanie piętra do kolejki

usun_pietro_z_kolejki(pietro) – usuwa obsłużone piętro

sprawdz_przyciski() – sprawdza przyciski (z debounce)

obsluz_przyjazd(pietro, kierunek) – obsługuje zatrzymanie na piętrze

wybierz_nastepne_pietro() – wybiera najbliższe piętro z kolejki

jedz_do_pietra() – realizuje ruch windy

🖥️ Komunikaty na wyświetlaczu LCD

Uruchamianie - Start windy...
Ruch windy - Jedzie na pietro: X
Postój -Winda na pietrze: X


Schemat połączeń:

Pin D1 → Przycisk piętro 1 (przycisk_pietro1)

Pin D2 → LCD RS

Pin D3 → LCD EN (E)

Pin D4 → LCD D4

Pin D5 → LCD D5

Pin D6 → LCD D6

Pin D7 → LCD D7

Pin D8 → Silnik krokowy – wejście IN1 (ULN2003)

Pin D9 → Silnik krokowy – wejście IN3 (ULN2003)

Pin D10 → Silnik krokowy – wejście IN2 (ULN2003)

Pin D11 → Silnik krokowy – wejście IN4 (ULN2003)

Pin D12 → Przycisk piętro 2 (przycisk_pietro2)

Pin D13 → Przycisk piętro 3 (przycisk_pietro3)


Analogowe wejścia

Pin A0 → Czujnik piętro 1 (czujnik_pietro1)

Pin A1 → Czujnik piętro 2 (czujnik_pietro2)

Pin A2 → Czujnik piętro 3 (czujnik_pietro3)

Pin A3 → (wolny / rezerwowy)

Pin A4 → (wolny / rezerwowy)

Pin A5 → (wolny / rezerwowy)
