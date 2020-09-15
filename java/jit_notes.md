# JIT notes

* Debugging JVM
* Za duzo abstrakcji
* Jezyki Strongtalk i Self, Lisp
* GraalVM i SubstrateVM
* HotSpot mniej wiecej Java 1.3
* PrintCompilation
  * Dla flagi n jest uzyty template po prostu
  * Made not entrant zamyka metode skompilowana na danym poziomie
* Podmianka body metody - bardzo rzadko, tylko w openJDK - np. w przypadku while(true) { } czyli niekonczacej sie metody
* Optymalizacje - kierowane tym jak dziala hardware
* Dlaczego dziedziczenie to if
* Podstawy optymalizacji
  * Usuniecie branchy
  * Przyblizenie danych (rejestry albo cache L1)
* HotSpot disassembler
* Uncommon trap
  * Jak idzie zawsze optymistycznym branchem to w pesymistycznym zostaje wskaznik na stary kod
* Morfy
  * Monomorfy - nic nie dziedziczy/implementuje
  * Bimorfy - dwa dziedzicza/implementuja
  * Megamorf - wiecej niz dwa
* Lock elission
  * Escape analysis - czy obiekt ucieka poza watek
  * Mozna np. nie alokowac wtedy obiekt na heapie tylko na stacku - oszczedzenie gc bo nie musimy sie obiektem dzielic
* Wlaczenie debugera - wylaczenie kompilatora; dlatego przy debugowaniu kod moze sie inaczej wykonywac niz bez
* Lock coarsening
* jitwatch
* Zmiana struktury danych jest zwykle duzo lepsza niz optymalizacja
* Minuty -> problem z db
* Sekundy -> struktury danych
* Milisekundy -> wtedy optymalizacja
* Frame mangling 
