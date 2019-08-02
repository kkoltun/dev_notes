# cURL

## Co to jest

cURL to klient pozwalający na komunikację z serwerami używając różnych protokołów - FTP, HTTP, HTTPS, SMTP i wiele innych.
Szeroki wybór opcji czyni z niego dość złożone narzędzie do komunikacji.

### Instalacja na Windows

**Jeżeli masz zainstalowany Git Bash na komputerze, masz także cURL.**

Sprawdzenie czy masz cURL wpisz w wierszu polecenia `curl --version`

Instalacja:
1) Pobierz i wypakuj pliki odpowiadające twojemu systemowi ze strony `https://curl.haxx.se/windows/`
2) Stwórz folder `curl` w wybranym miejscu, na przykład `C:\curl` i przenieś wypakowane pliki tam
3) Upewnij się że w folderze `<wybrana_lokalizacja>\curl\bin` jest plik `curl.exe`
4) Aby mieć dostęp do `curl` z wiersza polecenia dodaj do zmiennej systemowej `PATH` ścieżkę do folderu `bin`, na przykład: `C:\curl\bin`
5) Po wykonaniu wszystkich operacji sprawdź czy program działa w wierszu polecenia `curl --version`

### Instalacja na Linux i Mac

**cURL jest domyślnie zainstalowanym programem.**

### Pierwsze kroki

[Manpage programu](https://curl.haxx.se/docs/manpage.html)

#### Argumenty przydatne z punktu widzenia HTTP

* `-i`, `--include` wyświetl nagłówki odpowiedzi HTTP
* `-v`, `--verbose` wyświetl szczegóły działania programu (typowy verbose mode)
* `-X`, `--request` `<metoda HTTP>` pozwala wyspecyfikować metodę HTTP do użycia
* `-d`, `--data` `<dane>` pozwala przesłać dane w ciele zapytania
* `-I`, `--head` wysłanie zapytania z metodą `HEAD`
* `-H`, `--header` <nagłówek> wysłanie zapytania z określonym nagłówkiem

#### Przykładowe komendy

* `curl -i example.com` wysłanie zapytania `GET` pod adres `example.com` z włączonym wyświetlaniem nagłówków odpowiedzi
* `curl -i -X HEAD example.com` lub `curl -I example.com` wysłanie zapytania `HEAD` na adres `example.com` z włączonym wyświetlaniem nagłówków (bez tego cURL nie wyświetli nic)
* `curl -v -H "X-First-Name: Joe" http://example.com/` `GET` na adres `example.com` z nagłówkiem `X-First-Name: Joe` oraz trybem verbose (by zobaczyć nagłówek w zapytaniu)
