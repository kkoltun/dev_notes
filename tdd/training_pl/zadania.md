# Zadania z TDD

## Uwagi

### Test Driven Development

Wszystkie zadania najlepiej robić zgodnie z procesem Test Driven Development, w skrócie:
1. Napisanie testu w którym sprawdzamy czy kod spełnia wymaganie. Test nie przechodzi.
2. Napisanie najprostszego kodu który sprawia że test przechodzi.
3. Poprawki kodu i testów.
4. Przejście do kolejnych testów.

### Porównywanie zmiennych BigDecimal

#### W kodzie

Domyślna metoda `equals()` w klasie `BigDecimal` porównuje dwie liczby biorąc pod uwagę skalę - liczbę cyfr po przecinku.
Powoduje to, że porównywanie obiektów klasy `BigDecimal` może doprowadzić do nieprzewidzianych wyników, na przykład:

```java
BigDecimal x = new BigDecimal("1");
BigDecimal y = new BigDecimal("1.00");
System.out.println(x.equals(y)); // false
```

**W związku z tym, do porównywania obiektów `BigDecimal` w kodzie używamy ich metody `compareTo`, która porównuje liczby wewnątrz obietków.**
**Więcej informacji o metodzie [tutaj](https://www.geeksforgeeks.org/bigdecimal-compareto-function-in-java/).**

```java
BigDecimal x = new BigDecimal("1");
BigDecimal y = new BigDecimal("1.00");
System.out.println(x.compareTo(y) == 0); // true
```

#### W asercjach

Asercje `assertEquals` w JUnit oraz `assertThat(obj).isEqualTo(other)` w JAssert używają metody `equals()`, w związku z czym ich użycie do porównywania `BigDecimal` może być nietrafione.

```java
BigDecimal x = new BigDecimal("1");
BigDecimal y = new BigDecimal("1.00");
assertEquals(x, y); // nie przechodzi
assertThat(x).isEqualTo(y); // nie przechodzi
```

**W związku z tym, do porównywania obiektów `BigDecimal` w asercjach używamy metody `assertThat(liczba1).isEqualByComparingTo(liczba2)`, która wewnątrz używa metody `BigDecimal#compareTo()`.**
**Więcej informacji o porównywaniu liczb w AssertJ [tutaj](https://github.com/joel-costigliola/assertj-examples/blob/master/assertions-examples/src/test/java/org/assertj/examples/NumberAssertionsExamples.java).**

```java
BigDecimal x = new BigDecimal("1");
BigDecimal y = new BigDecimal("1.00");
assertEquals(0, x.compareTo(y)); // przechodzi, ale nie jest najczystszym podejściem
assertThat(x).isEqualByComparingTo(y); // przechodzi
```

## Rozszerzenie SimpleCalculator

**Potęga z liczby**:

Do klasy `SimpleCalculator` dodaj metodę `Integer power(Integer base, Integer expotent)`.

**Liczby parzyste**:

Do klasy `SimpleCalculator` dodaj metodę `Set<Integer> filterEvenNumbers(Set<Integer> numbers)`, która będzie przyjmować zbiór liczb całkowitych i zwracać te liczby ze zbioru które są parzyste.

**Liczenie pola i obwodu koła**:

Do klasy `SimpleCalculator` dodaj dwie metody przyjmujące średnicę koła i zwracające pole i obwód tego koła.
Przed napisaniem testów i metody zastanów się jakie są odpowiednie typy danych w przypadku tych metody.

**Liczenie kwoty brutto**:

Do klasy `SimpleCalculator` dodaj metodę która będzie przyjmować kwotę netto oraz wymiar podatku VAT (liczba procent) oraz obliczać kwotę brutto.
Weź pod uwagę odpowiednie zaokrąglanie zwracanej kwoty, metoda nie powinna zwracać więcej niż dwie cyfry po przecinku i odpowiednio zaokrąglać kwoty.

Materiały:
* [Jak obsłużyć pieniądze w Javie 1](http://www.javapractices.com/topic/TopicAction.do?Id=13)
* [Jak obsłużyć pieniądze w Javie 2](https://stackoverflow.com/questions/1359817/using-bigdecimal-to-work-with-currencies)

## Rozszerzenie TextCalculator

Do metody `calculate` klasy `TextCalculator` dodaj obsługę:
1. Liczb większych niż jednocyfrowe.
2. Liczb ujemnych.

## Nowa klasa BankAccount

Dodaj nową klasę `BankAccount`.

Zaimplementuj następujące metody:
1. `int getAmount()`
2. `void deposit(int amount)`
3. `void withdraw(int amount)`

Zaimplementuj następujące zachowanie konta:
1. Maksymalny debet równy `-1000`. Wypłata powyżej debetu: `IllegalStateException`.
2. Gdy ktoś wchodzi czyli wypłaca kwotę większą niż ma jest dostępna na koncie, należy mu naliczyć koszt debetu równy `5`.

## Prawdziwy serwis CurrencyService korzystający z API NBP

[Zadanie tutaj, **polecam**!](./nbp_client.md#)

## Pozostałe zadania z prezentacji

1. `Użycie Mockito - ćwiczenie 3`.
2. `TDD - ćwiczenie 1`, `TDD - ćwiczenie 2`.
