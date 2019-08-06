# Zadanie - klient HTTP

## Część pierwsza

1. Zapoznaj się ze specyfikają API: https://restcountries.eu/
2. Pobierz bibliotekę JSON oraz org.apache.commoins.io i dodaj je do projektu:
http://mvnrepository.com/artifact/org.json/json/20170516
https://mvnrepository.com/artifact/org.apache.commons/commons-io/1.3.2
3. Przejdź na stronę https://restcountries.eu/rest/v2/lang/pl i pobierz informacje dotyczące Polski.
4. Napisz kod który będzie przyjmował JSONa z danymi w zmiennej String i go interpretował. Przykładowy kod (z błędem :-)) poniżej:
```java
public static void main(String[] args) { //w kodzie jest celowo błąd!
  String json = "tutaj json";
  JSONObject obj = new JSONObject(json);
  String area = obj.get("area").toString();
  System.out.println("Polska ma " + area + " km2 powierzchni!");

  JSONArray languagesArr = (JSONArray) obj.get("languages");
  JSONObject languages = (JSONObject) languagesArr.get(0);
  String nativeLanguage = languages.get("nativeName").toString();
  System.out.println("Natywnym językiem w Polsce jest: " + nativeLanguage);
}
```

## Część druga

1. Java udostępnia szereg klas umożliwiających pobieranie zasobów z sieci.
Jedną z nich jest HTTPClients działająca w parze z HttpGet/HttpPost/HttpDelete/HttpPut.
Skorzystaj z przykładów http://bit.ly/2wPt1aZ i dodaj do aplikacji kod, który będzie pobierał dane ze strony.

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

Na przykład:
```java
public List<String> getCountriesWithSameLanguage(String countryName) {

}
```

5. Stwórz obiekt Country zawierający:
* nazwę państwa;
* nazwę stolicy;
* pole powierzchni;
* populację.

Napisz metodę która będzie przyjmowała nazwę państwa i zwracała obiekt Country z wypełnionymi wszystkimi polami.

Na przykład:
```java
public Country getCountryByName(String name) {
  // ...
}
```

## Część trzecia

1. Java udostępnia szereg klas umożliwiających mapowanie JSONa na obiekty.
Jedną z nich jest biblioteka gson dostarczona przez Google.
Zapoznaj się z biblioteką na stronie https://github.com/google/gson.

2. Napisz metodę która będzie przyjmowała nazwę państwa i zwracała stworzony obiekt wcześniej `Country`.
Tym razem nie parsuj JSONa manualnie, a wykorzystaj do tego biblitotekę.