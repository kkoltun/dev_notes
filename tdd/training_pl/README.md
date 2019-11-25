# TDD - materiały i zadania

[**Różne zadania domowe**](./zadania.md)

## Do oglądania

* [The Three Laws of TDD (Featuring Kotlin)](https://www.youtube.com/watch?v=qkblc5WRn-U)
* [Pragmatics of TDD to Evolve Design: part 1 (Venkat Subramaniam, USA)](https://www.youtube.com/watch?v=tzH_10zrGHQ)
* [DevTernity 2017: Ian Cooper - TDD, Where Did It All Go Wrong](https://www.youtube.com/watch?v=EZ05e7EMOLM)
* [DevTernity 2018: Sandro Mancuso - Does TDD Really Lead to Good Design?](https://www.youtube.com/watch?v=KyFVA4Spcgg)
* [Improving your Test Driven Development in 45 minutes - Jakub Nabrdalik](https://www.youtube.com/watch?v=2vEoL3Irgiw)

## Sprawdzenie kodu

Tak jak obiecywałem na szkoleniu, mogę sprawdzić Twój kod.
Musisz wrzucić kod na zdalne repozytorium git - najlepiej `github.com`.
Możesz to zrobić na dwa sposoby opisane niżej.

**Polecam cały oficjalny cykl tutoriali obsługi git w Intellij [tutaj](https://www.jetbrains.com/help/idea/using-git-integration.html).**

### Wrzucenie swojego kodu na moje repozytorium

Repozytorium publiczne na GitHub jest domyślnie tak skonfigurowane, że każdy może je pobrać, ale tylko jego założyciel może wrzucać na niego kod.
Aby dorzucić swoje zmiany na to repozytorium, musisz wykonać następujące kroki:
1. Wyślij mi swój identyfikator GitHub abym mógł wysłać zaproszenie do `Collaborators` tego repozytorium.
2. Zaakceptuj zaproszenie, które przyjdzie na maila.
3. Stwórz własny branch - [instrukcje tutaj](https://www.jetbrains.com/help/idea/manage-branches.html).
4. Przejdź na stworzony branch, wrzuć na niego zmiany (`commit`) i następnie prześli je na zdalne repozytorium - [instrukcje tutaj](https://www.jetbrains.com/help/idea/commit-and-push-changes.html).
5. Sprawdź czy zmiany pojawiły się na repozytorium zdalnym i daj mi znać że są gotowe do sprawdzenia.

### Stworzenie własnego `forka`

Tworzenie odgałęzień repozytorium - `fork` - jest często używaną opcją, gdy chcemy rozszerzać repozytorium stworzone przez innego programistę.
W wyniku `forka` otrzymujemy własne repozytorium, nad którym mamy pełną władzę, które jest kopią repozytorium bazowego.
Aby stworzyć własnego `forka` repozytorium TDD, musisz wykonać następujące kroki:
1. Zaloguj się do GitHub przez przeglądarkę i wejść na stronę repozytorium - [tutaj](https://github.com/kkoltun/training_tdd_examples).
2. Zrób `fork` repozytorium - przycisk znajduje się w prawym górnym rogu ekranu - [instrukcje tutaj](https://help.github.com/en/github/getting-started-with-github/fork-a-repo).
3. Ostatecznie GitHub powinien przenieść Cię na stronę Twojego repozytorium stworzonego ze źródłowego.
4. Teraz należy zmienić w Intellij adres repozytorium tak, by domyślny `remote` w gicie o nazwie `origin` nie wskazywał na moje repozytorium tylko na twoje nowe.
Ustawienie adresu danego remote (może być ich kilka) znajduje się w `VCS` -> `Git` -> `Remotes`.
Dla wpisu `origin` zmień adres na pobrany ze strony Twojego repozytorium GitHub - [instrukcje tutaj](https://help.github.com/en/github/using-git/which-remote-url-should-i-use).
5. Wyślij zmiany na zdalne repozytorium - [instrukcje tutaj](https://www.jetbrains.com/help/idea/commit-and-push-changes.html).
6. Daj mi znać że zmiany są gotowe do sprawdzenia - wyślij mi adres Twojego repozytorium.
