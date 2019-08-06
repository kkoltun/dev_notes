# Zadania rozszerzające aplikację CRUD movies

[Pobierz repozytorium z aplikacją stąd.](https://github.com/kkoltun/REST-movie-service)

## Dodanie pobierania reżyserów filmów

Bazując na otrzymanym kodzie kontrolera (klasa `MovieController`), dodaj do aplikacji możlwiość pobrania listy reżyserów filmów w kolekcji:
* adres: `/directors`
* metoda: `GET`
* zwraca: lista reżyserów filmów w kolekcji
* zadbaj o to, by w odpowiedzi była lista reżyserów bez powtórzeń

Aby sprawdzić dodaną metodę, spróbuj pobrać listę reżyserów, po czym dodaj nowy film i znów pobierz listę.

Pamiętaj, że gotowa metoda może zwracać listę obiektów klasy `String`.
Biblioteka `Spring-Boot` razem z mapperem same zadbają o to by zamienić listę na JSON z listą który przyjdzie w odpowiedzi na zapytanie.

## Dodanie pobierania daty wydania konkretnego filmu

Dodaj do aplikacji możliwość pobrania daty wydania filmu:
* adres: `/movies/{id}/release_date`
* metoda: `GET`
* zwraca: datę wydania filmu o danym id

Aby sprawdzić dodaną metodę, pobierz datę wydania istniejącego w kolekcji filmu, następnie zmień datę jego wydania metodą `PATCH` i znów ją pobierz.
