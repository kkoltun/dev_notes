# Zadania z JVM

## Zadanie 1: Przećwiczenie debuggera w Intellij

Prześledzić wykonanie jednego z algorytmów.
Operacje do wykonania:
* przejście krok po kroku po funkcji;
* wejście w aktualnie wykonywaną funkcję;
* podejrzenie zmiennych w aktualnie wykonywanej funkcji;
* wykonanie operacji na jednej z dostępnych zmiennych (prawym na zmienną -> Evaluate expression)

Spory tutorial składający się z dwóch kroków:
* [Tworzenie nowej aplikacji w Intellij - zadanie proste, ale tutorial zawiera wiele bardzo przydanych narzędzi, polecam](https://www.jetbrains.com/help/idea/creating-and-running-your-first-java-application.html)
* [Debugowanie stworzonej aplikacji - powtórka i rozszerzenie tego co robiliśmy na zajęciach](https://www.jetbrains.com/help/idea/debugging-your-first-java-application.html)

## Zadanie 2: Program przyjmujący argumenty

Napisz program który będzie przyjmował argumenty w postaci napisanych po angielsku cyfr i wyświetlał ich polskie tłumaczenie.

Przykłady argumentów oraz wyświetlanego przez program tekstu:
* `one two` -> `jeden dwa`
* `nine` -> `dziewiec`
* <brak argumentów> -> `brak liczb`
* <nieznane cyfry/teksty> -> `nieznany tekst`

**W razie problemów z działaniem programu, użyj debuggera.**

## Zadanie 3: Program przyjmujący więcej argumentów - opcje oraz imiona

Zmienić program Hello z zajęć tak, aby przyjmował argumenty oraz imiona:
Hello <argumenty> <jedno lub więcej imion>

Argumenty to teksty zaczynające się od jednego lub dwóch myślników. Przyjmowane argumenty to:
1. `-u` oraz `--upper-case` i po podaniu jednego z nich, wyświetlał podane imiona wielkimi literami
2. `-l` oraz `--lower-case` i po podaniu jednego z nich, wyświetlał podane imiona małymi literami

Warunki:
1. Niech program ignoruje nieznane argumenty czyli teksty po jednym lub dwóch myślnikach, które nie są wyszczególnione powyżej.
2. Argumenty muszą być podane przed imionami.

### Przykłady do przetestowania

Działanie bez argumentów, same imiona:
* <brak argumentów> -> `Hello, Unknown`
* `Karol Ola` -> `Hello, Karol, Ola`

Działanie z argumentami powiększającymi litery:
* `--upper-case marek ilona` -> `Hello, MAREK, ILONA`
* `--upper-case` -> `Hello, UNKNOWN"
* `-u Gabriel Marek anna` -> `Hello, GABRIEL, MAREK, ANNA`

Działanie z argumentami pomniejszającymi litery:
* `-l Maria` -> `Hello, maria`
* `--lower-case Gigi Adrian` -> `Hello, gigi, adrian`

### Przykładowy zarys rozwiązania

1. Wyjście z programu który działa bez argumentów modyfikujących wyświetlanie imion.
2. Dodanie argumentu `-u` lub `--upper-case`:
  * wyszukanie tego tekstu wśród wszystkich podanych argumentów;
  * jeśli został podany to ustawienie zmiennej boolean oznaczającej powiększenie tekstu na `true`;
3. Usunięcie wszystkich tekstów zaczynających się myślnikami z listy podanych argumentów (by ich nie wyświetlić jako imion);
4. Przeiterowanie po pozostałych argumentach (imionach) i wyświetlenie ich razem z oddzieleniem przecinkiem;
5. Jeśli zmienna oznaczająca powiększanie liter jest `true` to powiększenie liter przed wyświelteniem.
6. Powtórzenie kroków i dodanie argumentu `-l` lub `--lower-case`.
7. Przetestowanie programu na wyżej wymienionych przypadkach.

**W razie problemów z działaniem programu, użyj debuggera.**

## Zadanie 4: Kompilacja i manualne wykonanie programu

Wzorując się na slajdach oraz na ćwiczeniu wykonanym na zajęciach, skompiluj oraz wykonaj prosty program składający się z jednej klasy.
Użyj do tego celu wiersza polecenia oraz narzędzi `javac` oraz `java`.
Zwróć uwagę na różnicę pomiędzy podaniem do programu ścieżki do pliku, a podaniem nazwy klasy razem z paczką.

## Zadanie 5: Class loadery oraz wyjątki rzucane przez JVM

Wykonaj zadania 5 oraz 9 podane w prezentacji.

## Zadanie 6: Zbadanie działania Intellij za pomocą Visual VM (bez GC)

1. Włącz Intellij, otwórz w programie wybrany projekt

2. Włącz program Visual VM, zacznij monitorować Intellij

3. W zakładce `Overview`:
  * Przeczytaj jakie arugmenty są podawane domyślnie do JVM w którym pracuje Intellij.
  * Który z tych argumentów ustawia odpowiedni Garbage Collector?
  * Sprawdź w internecie znaczenie wybranych czterech argumentów.

4. W zakładce `Monitor`:
  * Przeczytaj ile Heapa aktualnie używa Intellij.
  * Przeczytaj jaki jest ogólnie rozmiar heapa (`Heap size` vs `Used heap`).
  * Wymuś Garbage Collection przyciskiem `Perform GC`.

**Uwaga: ogólnie rzecz biorąc, nie da się przewidzieć ani wymusić na Garbage Collectorze zebrania śmieci.**
**Przycisk wywołuje metodę `System.gc()` która jest ogólnie sugestią do Garbage Collectora, która może, ale nie musi zostać wykonana!**

5. W zakładce `Sampler` uruchom próbnik pamięci oraz zbadaj:
  * Która klasa ma najwięcej obiektów zaalokowanych w pamięci. 
  * Jaki procent wszystkich obiektów stanowią obiekty żywe (czy zgadza się to z hipotezą generacyjną?).

## Zadanie 7: Zbadanie Garbage Collectora na przykładzie Intellij za pomocą Visual VM

1. W Visual VM przełącz na zakładkę `Visual GC`.

2. Aby było łatwiej zaobserwować różne procesy, możesz przełączyć częstotliowość odświeżania z `Auto` na `100 ms`.

3. Aby wywołać większe użycie pamięci:
  * Poprzeskakuj w programie po plikach z kodem.
  * Uruchom budowanie projektu od zera (`Build`->`Rebuild project`).

4. Procesy do zaobserwowania:
  * `Minor Garbage Collection` czyli wyczyszczenie `Edenu` i jednej z przestrzeni `Survivor` oraz przeniesienie żywych obiektów do drugiej przestrzeni `Survivor`
  * `Full Garbage Collection` czyli to co w `Minor GC` razem z czyszczeniem `Old Generation`.

## Zadanie 8: Zmiana argumentów przekazywanych do Intellij

Argumenty podawane do JVM w którym uruchamia się Intellij są ustawiane w plikach:
  * Intellij 32-bitowy: <folder_z_programem>/bin/idea.exe.vmoptions
  * Intellij 64-bitowy: <folder_z_programem/bin/idea64.exe.vmoptions

Aby poznać który plik jest używany, sprawdź opcje w obu z nich, a następnie odczytaj w VisualVM które opcje zostały podane do JVM. 

**Uwaga:**

1. Zmiana argumentów może spowodować niedziałanie Intellij. Przed jakimikolwiek zmianami zapisz aktualną, działającą wersję pliku z opcjami na boku.

2. Po każdej zmianie argumentów należy zresetować Intellij, przełączyć monitorowanie Visual VM na nową instancję programu i sprawdzić w zakładce `Overview` czy nowe opcje zostały załadowane.

**Zmiany do przetestowania:**

1. Zmiana Garbage Collectora z klasycznego `Concurrent Mark Sweep` na `G1`:
  * z opcji: `-XX:+UseConcMarkSweepGC`
  * na opcję: `:-XX:+UseG1GC`
  * komentarz: wiele osób stwierdza, że po tej zmianie Intellij znacząco przyspiesza. Warto zaobserwować jakie skutki ma zmiana w zakładce Visual GC w programie Visual VM.

2. Wyłączenie JIT:
  * dodanie opcji: `-Xint`
  * komentarz: Intellij powinien bardzo poważnie zwolnić. Czy wiesz dlaczego tak się dzieje?
