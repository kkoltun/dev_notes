# Zadania do zajęć z sieci i HTTP

## Podstawy sieci - teoria

1. Jak się nazywa protokół, który dba o odpowiednie adresowanie w sieci niezależne od infrastruktury?
2. Jakie są dwa typy adresów w sieci? Dlaczego mając jeden wprowadzono drugi?
3. Podaj adres za pomocą którego można przesyłać wiadomości w obrębie tego samego komputera. Podaj jego dwie postacie (słowna i cyfrowa).
3. Jak się nazywa protokół, który mówiąc oględnie dba o niezawodne przesyłanie wiadomości?
4. Podaj trzy przykłady protokołów aplikacji - tych które dbają o to by komunikacja "przebiegała w tym samym języku".
5. W jaki sposób pod jednym adresem mogą być wystawione różne usługi?
6. Jak nazywa się system dzięki któremu nie musimy zapamiętywać cyfrowych adresów serwerów?

## Podstawy sieci - zadania z układania adresów URL:

W każdym z zadań określ każdy wspomniany parametr wewnątrz URL.

1. Wykonaj połączenie w przeglądarce:
  * Używając protokołu: `HTTPS`
  * Z serwerem: `www.google.com`
  * Pod portem: `443`jest to domyślny port HTTPS, ale tym razem napisz go w URL)

2. Wykonaj połączenie w przeglądarce:
  * Protokół: `HTTPS`
  * Serwer: `pl.wikipedia.org`
  * Ścieżka do zasobu: `/wiki/Miedzianka_szmaragdowa`
  * Fragment artykułu: `Ekologia_i_zachowanie`

3. Wykonaj połączenie w przeglądarce:
  * Protokół: `HTTPS`
  * Serwer: `www.youtube.com`
  * Ścieżka: `/results`
  * Parametr URL: nazwa: `search_query`; wartość: `http+explained`

4. Wykonaj połączenie w przeglądarce:
  * Protokół: `HTTP`
  * Serwer: `www.portquiz.net`
  * Port: `8080`

5. Wykonaj połączenie w przeglądarce:
  * Protokół: `FTP`
  * Serwer: `speedtest.tele2.net`
  * (To jest publiczny serwer FTP, nie radzę ściągać z niego plików)
  
6. Wykonaj połączenie w przeglądarce (określ login i hasło wewnątrz URL):
  * Protokół: `FTP`
  * Serwer: `test.rebex.net/`
  * Login: `demo`
  * Hasło: `password`
  * Ścieżka: `/readme.txt`

## HTTP - zadania

### Metody HTTP

Wykonaj poniższe polecenia za pomocą cURL lub Postman.

1. Pobierz same nagłówki dla zasobu `https://www.ics.uci.edu/~fielding/pubs/dissertation/fielding_dissertation.pdf`. Jakiej wielkości jest plik pod tym adresem?
2. Pobierz dozwolone metody HTTP dla zasobu `https://api.github.com/users`
3. Wiedząc że serwis `api.github.com` umożliwia poznanie repozytoriów użytkownika pod adresem `/users/{username}/repos` pobierz repozytoria dla użytkownika `kkoltun`
4. Wiedząc że serwis `api.github.com` umożliwia poznanie konkretnego repozytorium użytkownika pod adresem `/repos/{username}/{repository_name}` pobierz repozytorium użytkownika `torvalds` o nazwie `linux`
5. Spróbuj usunąć pobrane w punkcie wyżej repozytorium. Jak myślisz, dlaczego serwer odpowiedział w ten sposób?

Jeśli używasz Linuksa lub Git Bash w Windowsie, aby sformatować odpowiedź w formacie JSON pochodzącą z cURL możesz wykonać przekierowanie (*pipe*) do programu json_pp.
Dla przykładu:
* komenda `curl https://api.punkapi.com/v2/beers` pobierze niesformatowaną listę alkoholi;
* komenda `curl https://api.punkapi.com/v2/beers | json_pp` przekieruje tę niesformatowaną listę do programu `json_pp` który ją sformatuje i wyświetli.

[Więcej informacji o pipes - uwaga, niektóre komendy przedstawione w tutorialu są niedostępne w Git Bash](https://www.geeksforgeeks.org/piping-in-unix-or-linux/)

### Obsługa lokalnie uruchomionej aplikacji z zajęć

Wstęp:
1. Na [tym repozytorium GitHub](https://github.com/kkoltun/REST-movie-service) znajduje się przykładowa CRUDowa aplikacja. Zapoznaj się z kodem kontrolera.
2. Pobierz jar z aplikacją [stąd](https://github.com/kkoltun/REST-movie-service/releases/download/0.4/movies-0.4.jar).
3. Uruchom aplikację komendą `java -jar movies-0.4.jar`.

Aplikacja działa pod portem `8081` i wystawia następujące zasoby:
* `/movies` - dostęp do wszystkich filmów;
* `/movies/{id}` - dostęp do konkretnego filmu.

Pamiętaj że aplikacja przeważnie ignoruje id filmu przesłane w ciele wiadomości.

Operacje w aplikacji:
1. Pobierz wszystkie zapisane w aplikacji filmy zapytaniem `GET` pod adres `http://localhost:8081/movies`
2. Zbadaj wszystkie możliwe metody do wykonania na zasobie `/movies` oraz na konkretnym filmie z id równym 1
3. Dodaj nowy film do kolekcji oraz zbadaj odpowiedź serwera:
  * tytuł: Leviathan
  * reżyser: Andrey Zvyagintsev
  * wydany: 13 listopada 2014
4. Spróbuj dodać nowy film do kolekcji ale nie wpisuj reżysera oraz daty wydania. Zbadaj odpowiedź serwera. 
5. Spróbuj usunąć nieistniejący film w kolekcji.
6. Zmień tytuł jednego z filmów w kolecji.
7. Zamień jeden z filmów na inny.

### (Dla chętnych) Dodanie nowego zasobu do aplikacji

[Zadanie tutaj](tasks/movies_extension.md)

### (Dla chętnych) Własny klient HTTP

[Zadanie tutaj](tasks/java_http_client.md)
