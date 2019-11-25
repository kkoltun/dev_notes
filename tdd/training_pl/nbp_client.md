# Prawdziwy serwis CurrencyService korzystający z API NBP

## API NBP

NBP wystawia internetowe API REST do pobierania kursów walut.
Zapoznaj się z dokumentacją API [tutaj](http://api.nbp.pl/en.html).
Pod różnymi adresami dostępnę są różne dane dotyczące kursu walut, ceny złota i innych.

Pod adresem `http://api.nbp.pl/api/exchangerates/rates/{typ_tabeli}/{kod_waluty}/{data}` można pobrac kurs danej waluty:
* `{typ_tabeli}` - są tabele A, B i C, zawierające różne dane. W najprostszym przypadku interesuje tabela A.
* `{kod_waluty}` - każda waluta ma swój kod - złotówka to `PLN`, dolar `USD`, euro `EUR` i tak dalej.
* `{data}` - data w formacie `YYYY-MM-DD` lub tekst `today`. Pamiętaj że kursy walut są zwracane tylko dla dni roboczych.

Przykładowe użycie API:
* Wysłanie zapytania pod adres `http://api.nbp.pl/api/exchangerates/rates/A/usd/today` pobiera dzisiejszy kurs dolara.
* Wysłanie zapytania pod adres `http://api.nbp.pl/api/exchangerates/rates/A/eur/2019-11-22` pobiera kurs euro z 22 listopada.

## Format danych 

Domyślnie dane z API są pobierane w formacie JSON. Można je także pobrać w formacie XML.
Pobrawszy dane w formacie JSON możemy obsłużyć je jako `String` i manualnie wyszukiwać wartości które nas interesują.
To sprawdzi się na początku, jednak warto wziąć pod uwagę użycie specjalnej biblioteki do parsowania JSONa, na przykład [JSON in Java](https://mvnrepository.com/artifact/org.json/json).

## Klient HTTP w Javie

Aby móc wysyłać zapytania do internetu pod API NBP, potrzebny jest nam klient HTTP.
Nie musimy go pisać samodzielnie, jest wiele bibliotek które realizują to zadanie.
Jedną z nich jest dostarczana razem z Javą począwszy od wersji 9.
[Tutaj](https://openjdk.java.net/groups/net/httpclient/recipes.html) możesz znaleźć jego przykładowe użycie.

## Przykładowy kod pobierający kurs walut z NBP API

1. Dodaj do projektu [JSON in Java](https://mvnrepository.com/artifact/org.json/json).
2. W paczce `dev.karolkoltun.currency` stwórz nowy plik `ExampleCurrencyClient` i wypróbuj kod zamieszczony [tutaj](./ExampleCurrencyClient.java).
3. Zbadaj przykładowy kod i przerób go tak, by pobierał kursy innych walut dla innych dat.
4. Przykładowy kod pobiera średni kurs waluty. Przerób go by pobierał kurs kupna `bid` i sprzedaży `ask` danej waluty. Te kursy są w przechowywane w tabeli C.
5. Dodaj do klasy `ExampleCurrencyClient` metody:
  * `public double getTodayAverageRate(String currencyCode)` - pobiera średni dzisiejszy kurs wybranej waluty.
  * `public double getTodayBidRate(String currencyCode)` - pobiera dzisiejszy kurs kupna wybranej waluty.
  * `public double getTodayAskRate(String currencyCode)` - pobiera dzisiejszy kurs sprzedaży wybranej waluty.
6. Dodaj takie same metody które będą przyjmowały dodatkowo datę dla której należy pobrać kurs.
7. W przypadku w którym serwer nie może znaleźć danych o które zapyta klient, zwraca odpowiedź HTTP `404`.
[Tutaj](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status/404) możesz poznać szczegóły tej odpowiedzi.
Zadbaj o to, by w razie takiego błędu aplikacja rzucała wyjątek `RateNotFoundException`.

## Zadanie

Bazując na przykładowym kodzie, stwórz nową implementację interfejsu `CurrencyService`, która będzie przeliczać waluty na podstawie aktualnego kursu NBP.
