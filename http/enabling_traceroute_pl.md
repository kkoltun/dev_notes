# Traceroute

## Co to jest

Traceroute (w niektórych systemach tracert) to program do badania trasy pakietów w sieci IP.

## Użycie w Windows

W systemach Windows traceroute jest domyślnie zainstalowany.

Użycie traceroute:
1. Włącz wiersz polecenia
2. Wpisz `tracert <adres_strony>` i kliknij `ENTER`
3. Obserwuj kolejne kroki na trasie pakietu

![windows_usage](./image/traceroute_win_10_pl/usage.png)

Przykładowe komendy:
* `tracert www.google.com`
* `tracert 127.0.0.1` (adres loopback)

Traceroute domyślnie w systemie Windows działa dość wolno w porównaniu do implementacji na Linuksie.
Aby przyspieszyć działanie można użyć opcji `-d` by wyłączyć rozwijanie nazw serwerów oraz `-w 100` by ograniczyć timeout do 100 milisekund.
Przykładowa komenda po modyfikacjach: `tracert -d -w 100 www.google.com`.

## Użycie w systemie Ubuntu

W systemie Ubuntu zazwyczaj należy najpierw zainstalować narzędzie.
W tym celu w terminalu należy wpisać:
`sudo apt-get install traceroute`

Po instalacji użycie traceroute:
1. Włącz terminal
2. Wpis `traceroute <adres_strony>`
3. Obserwuj kolejne kroki na trasie pakietu

Przykładowe komendy:
* `traceroute www.google.com`
* `traceroute 127.0.0.1` (adres loopback)

## Użycie w systemie Mac



## Uwagi

* Traceroute nie używa protokołu http/https więc nie należy wskazywać adresów zaczynając od tego protokołu (np. `traceroute http://www.google.com` jest błędnym adresem);
* Implementacje traceroute na Windowsie i Linuksie różnią się - w tym pierwszym używa się protokołu ICMP, w drugim UDP;
* Wynik działania traceroute można nałożyć na mapę świata - https://stefansundin.github.io/traceroute-mapper/;

