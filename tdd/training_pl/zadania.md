# Zadania z TDD

```
Wszystkie zadania najlepiej robić zgodnie z procesem Test Driven Development, w skrócie:
1. Napisanie testu w którym sprawdzamy czy kod spełnia wymaganie. Test nie przechodzi.
2. Napisanie najprostszego kodu który sprawia że test przechodzi.
3. Poprawki kodu i testów.
4. Przejście do kolejnych testów.
```

## Rozszerzenie `SimpleCalculator`

**Potęga z liczby**:

Do klasy `SimpleCalculator` dodaj metodę `Integer power(Integer base, Integer expotent)`.

**Liczby parzyste**:

Do klasy `SimpleCalculator` dodaj metodę `Set<Integer> filterEvenNumbers(Set<Integer> numbers)`, która będzie przyjmować zbiór liczb całkowitych i zwracać te liczby ze zbioru które są parzyste.

**Liczenie pola i obwodu koła**:

Do klasy `SimpleCalculator` dodaj dwie metody przyjmujące średnicę koła i zwracające pole i obwód tego koła.
Przed napisaniem testów i metody zastanów się jakie są odpowiednie typy danych w przypadku tych metody.

**Liczenie kwoty brutto**:

Do klasy `SimpleCalculator` dodaj metodę która będzie przyjmować kwotę netto oraz wymiar podatku VAT (liczba procent) oraz obliczać kwotę brutto.
Weź pod uwagę odpowiednie zaokrąglanie zwracanej kwoty, metoda nie powinna zwracać więcej niż dwie cyfry po przecinku.

Materiały:
* [Jak obsłużyć pieniądze w Javie 1](http://www.javapractices.com/topic/TopicAction.do?Id=13)
* [Jak obsłużyć pieniądze w Javie 2](https://stackoverflow.com/questions/1359817/using-bigdecimal-to-work-with-currencies)

## Rozszerzenie TextCalculator

Do metody `calculate` klasy `TextCalculator` dodaj obsługę:
1. Liczb większych niż jednocyfrowe.
2. Obsługa liczb ujemnych.

## Nowa klasa `BankAccount`

Dodaj nową klasę `BankAccount`.

Zaimplementuj następujące metody:
1. `int getAmount()`
2. `void deposit(int amount)`
3. `void withdraw(int amount)`

Zaimplementuj następujące zachowanie konta:
1. Maksymalny debet równy `-1000`. Wypłata powyżej debetu: `IllegalStateException`.
2. Gdy ktoś wchodzi czyli wypłaca kwotę większą niż ma jest dostępna na koncie, należy mu naliczyć koszt debetu równy `5`.

## Pozostałe zadania z prezentacji

1. `Użycie Mockito - ćwiczenie 3`.
2. `TDD - ćwiczenie 1`, `TDD - ćwiczenie 2`.
