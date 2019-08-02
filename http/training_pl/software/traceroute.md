# Traceroute

## Co to jest

Traceroute (w niektórych systemach tracert) to program do badania trasy pakietów w sieci IP.

## Instalacja w Windows

W systemach Windows traceroute jest domyślnie zainstalowany.

## Instalacja w systemie Ubuntu

W systemie Ubuntu zazwyczaj należy najpierw zainstalować narzędzie.
W tym celu w terminalu należy wpisać:
`sudo apt-get install traceroute`

## Instalacja w systemie macOS

Instrukcje [tutaj](https://macreports.com/how-to-run-traceroute-on-macos/).

## Użycie

Użycie traceroute:
1. Włącz wiersz polecenia (Windows) lub terminal (Ubuntu, Mac)
2. Wpisz `tracert <adres_strony>` (Windows) lub `traceroute <adres_strony>` (Linux, MacOS) i kliknij `ENTER`
3. Obserwuj kolejne kroki na trasie pakietu

![traceroute](../image/traceroute.png)

Przykładowe komendy na Windows:
* `tracert www.google.com`
* `tracert 127.0.0.1` (adres loopback)

Przykładowe komendy na Linux, MacOS:
* `traceroute www.google.com`
* `traceroute 127.0.0.1` (adres loopback)

### Uwagi co do działania w systemie Windows

Traceroute domyślnie w systemie Windows działa dość wolno w porównaniu do implementacji na Linuksie.
Aby przyspieszyć działanie można użyć opcji `-d` by wyłączyć rozwijanie nazw serwerów oraz `-w 100` by ograniczyć timeout do 100 milisekund.
Przykładowa komenda po modyfikacjach: `tracert -d -w 100 www.google.com`.

## Uwagi ogólne

* Traceroute nie używa protokołu http/https więc nie należy wskazywać adresów zaczynając od tego protokołu (np. `traceroute http://www.google.com` jest błędnym adresem);
* Implementacje traceroute na Windowsie i Linuksie różnią się - w tym pierwszym używa się protokołu ICMP, w drugim UDP;
* Wynik działania traceroute można nałożyć na mapę świata - https://stefansundin.github.io/traceroute-mapper/;

