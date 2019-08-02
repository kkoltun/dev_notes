# Włączanie usługi telnet

## Windows 7

## Windows 10

1. Uruchom wiersz polecenia jako administrator.
Najłatwiej otworzyć menu start i wpisać `cmd`.
Wtedy Windows sam znajdzie wiersz polecenia i wyświetli go na liście.

![step_1](./image/telnet_win_10_pl/step_1.png)

2. W wierszu polecenia wpisz `dism /online /Enable-Feature /FeatureName:TelnetClient` i kliknij `ENTER`.

![step_2](./image/telnet_win_10_pl/step_2.png)

3. Powinien uruchomić się proces włączania usługi Telnet. Na screenshocie widać wynik procesu który zakończył się pomyślnie.

![step_3](./image/telnet_win_10_pl/step_3.png)

4. Teraz możesz włączyć klient telnet.
Wystarczy w okienku wiersza poleceń w którym zakończył się proces włączania wpisać `telnet` i kliknąć `ENTER`.

![step_4](./image/telnet_win_10_pl/step_4.png)

5. Klient telnet został włączony.
Teraz można wpisywać różne komendy, np. .
Aby wyjść z niego należy wpisać `quit` lub `q` i nacisnąć `ENTER`.
Można także po prostu zamknąć okno wiersza poleceń.

![step_5](./image/telnet_win_10_pl/step_5.png)

Narzędzie można uruchomić także tak samo jak uruchomiony został wiersz polecenia:
1. Włączenie menu start.
2. Wpisanie `telnet`.
3. Wybranie opcji `telnet` z listy znalezionych programów.

## Ubuntu

Telnet domyślnie wchodzi w skład Ubuntu.