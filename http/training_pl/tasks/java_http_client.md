# Zadanie - klient HTTP

## Część pierwsza

1. Zapoznaj się ze specyfikają API: https://restcountries.eu/
2. Rozpocznij nowy projekt. Dodaj do niego biblioteki:
* [JSON](https://mvnrepository.com/artifact/org.json/json/20180813)
* [Commons IO](https://mvnrepository.com/artifact/commons-io/commons-io/2.6)
3. Przejdź [tutaj](https://restcountries.eu/rest/v2/lang/pl) i pobierz informacje dotyczące Polski.
4. Napisz kod który będzie przyjmował JSONa z danymi w zmiennej String i go interpretował. Przykładowy kod poniżej:
```java
public static void main(String[] args) {
  // w kodzie jest celowo błąd!
  String json = "tutaj json";
  JSONObject obj = new JSONObject(json);
  String area = obj.get("area").toString();
  System.out.println("Polska ma " + area + " km2 powierzchni!");

  JSONArray languagesArr = (JSONArray) obj.get("language");
  JSONObject languages = (JSONObject) languagesArr.get(1);
  String nativeLanguage = languages.get("nativeName").toString();
  System.out.println("Natywnym językiem w Polsce jest: " + nativeLanguage);
}
```

## Część druga

1. Java udostępnia szereg klas umożliwiających pobieranie zasobów z sieci.
Jedną z nich jest [Apache HTTPClient](https://mvnrepository.com/artifact/org.apache.httpcomponents/httpclient/4.5.9).
Biblioteka działa na zasadzie: stwórz klient, stwórz obiekt zapytania (klasa `HttpGet`, `HttpPost` lub inne), wykonaj zapytanie.
[Tutaj](https://hc.apache.org/httpcomponents-client-ga/tutorial/html/fundamentals.html) oraz [tutaj](https://www.vogella.com/tutorials/ApacheHttpClient/article.html) można poznać przykłady użycia.
Użyj biblioteki by pobierać dane ze strony `restcountries`.

2. Napisz metodę która będzie przyjmowała kod języka i zwracała nazwy państw w których tym językiem się operuje.

Na przykład:

```java
public List<String> getCountriesByLanguageCode(String languageCode) {
  // ...
}
```

3. Napisz metodę która będzie przyjmowała nazwę regionu i zwracała nazwy państw razem z populacją posortowane od największej.

Na przykład:
```java
public Map<String, int> getCountriesWithPopulation(String regionName) {
  // ...
}
```

4. Napisz metodą która będzie przyjmowała nazwę państwa i zwracała państwa w których mówi się w tym samym języku.
Jeżeli pod daną nazwą znajdzie się więcej niż jedno państwo, niech metoda wyrzuca `IllegalArgumentException ` z odpowiednią wiadomością w środku.

Na przykład:
```java
public List<String> getCountriesWithSameLanguage(String countryName) {
  // ...
}
```

5. Stwórz obiekt Country zawierający:
* nazwę państwa;
* nazwę stolicy;
* pole powierzchni;
* populację.

Napisz metodę która będzie przyjmowała nazwę państwa i zwracała obiekt Country z wypełnionymi wszystkimi polami.
Jeżeli pod daną nazwą znajdzie się więcej niż jedno państwo (na przykład pod nazwą `pol`), niech metoda wyrzuca `IllegalArgumentException ` z odpowiednią wiadomością w środku.

Na przykład:
```java
public Country getCountryByName(String name) {
  // ...
}
```

## Część trzecia

1. Java udostępnia szereg klas umożliwiających mapowanie JSONa na obiekty.
Przykładowe biblioteki:
* [gson](https://github.com/google/gson) dostarczony przez Google; [tutaj jeden z tutoriali](https://www.baeldung.com/gson-deserialization-guide); [maven](https://mvnrepository.com/artifact/com.google.code.gson/gson/2.8.5)
* [Jackson](https://github.com/FasterXML/jackson) używany przez między innymi Springa; [tutaj tutoriale](https://github.com/eugenp/tutorials/tree/master/jackson) [maven](https://mvnrepository.com/artifact/com.fasterxml.jackson.core/jackson-databind/2.9.9.2)

2. Napisz metodę która będzie przyjmowała nazwę państwa i zwracała stworzony obiekt wcześniej `Country`.
Tym razem nie parsuj JSONa manualnie, a wykorzystaj do tego biblitotekę.

3. W poprzedniej części zostało wspomniane, że przy wysłaniu zapytania do `restcountries` z nazwą państwa, serwis zwraca listę pasujących obiektów.
Można to sprawdzić wysyłając zapytanie pod adres `restcountries.eu/rest/v2/name/pol` które powinno zwrócić dwa państwa - Polskę i Polinezję Francuską.

Napisz metodę która zamiast jednego obiektu `Country` będzie zwracała ich listę. Do mapowania JSONa z listą państw na obiekt listy użyj wybranej biblioteki.