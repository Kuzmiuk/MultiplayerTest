MultiKama




Opis



Projekt przedstawia prostą grę multiplayer w Unreal Engine 5.3 napisaną w C++. Rozgrywka działa w modelu klient-serwer z wykorzystaniem LAN.



W projekcie zaimplementowano:



\- system tworzenia i dołączania do sesji multiplayer (LAN), ( działa tylko jak masz włączony Steam ) 

\- lobby z przejściem do mapy gry (Server Travel, Seamless Travel),

\- replikację ruchu, animacji oraz stanu postaci,

\- system walki obejmujący podnoszenie broni, strzelanie, przeładowanie oraz celowanie,

\- system zdrowia, tarczy i eliminacji gracza z respawnem,

\- synchronizację statystyk graczy (Health, Shield, Score, Defeats) z wykorzystaniem PlayerState i GameState,

\- HUD wyświetlający aktualne informacje o stanie gracza,

\- podstawową optymalizację sieciową z wykorzystaniem replikacji oraz RPC,

\- implementację głównych mechanik w C++, natomiast konfigurację i elementy wizualne wykonano w Blueprintach.

* add plugins ( Online Subsytem Steam ) 



Uruchomienie



1\. Uruchom plik MultiKama.





&#x20;Rozgrywka

\- E – podniesienie lub zmiana broni.

\-LPM – strzał.

\- PPM – celowanie



\- Q – przeładowanie.

R - Start game w lobby



&#x20;Przedmioty



\- \*\*Kwadrat\*\* – bron.

\- \*\*Stojak\*\* – Shield (tarcza).



