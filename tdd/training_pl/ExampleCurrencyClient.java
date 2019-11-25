package dev.karolkoltun.currency;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

import static java.lang.String.format;

public class ExampleCurrencyClient {
  private static final URI NBP_URI = URI.create("http://api.nbp.pl/api/exchangerates/rates/A/eur/2019-11-22");
  
  public static void main(String[] args) throws IOException, InterruptedException {

    System.out.println(getBanner());

    HttpClient client = HttpClient.newHttpClient();

    HttpRequest request = HttpRequest.newBuilder()
        .uri(NBP_URI)
        .header("Accept", "application/json")
        .build();

    System.out.println("Sending request to:" + NBP_URI.toString());
    
    HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

    JSONObject receivedObject = new JSONObject(response.body());
    
    System.out.println("Received response:\n" + receivedObject.toString(2));

    String table = receivedObject.getString("table");
    String currencyCode = receivedObject.getString("code");
    
    JSONArray rates = receivedObject.getJSONArray("rates");
    JSONObject firstRate = rates.getJSONObject(0);
    float rate = firstRate.getFloat("mid");
    String dateStr = firstRate.getString("effectiveDate");

    System.out.println(format("Rate in table %s for currency %s in %s = %f", table, currencyCode, dateStr, rate));
  }
  
  private static String getBanner() {
    return "                                                         ,--,                                          ,----, \n" +
        "         ,--.           ,-.----.                      ,---.'|                              ,--.      ,/   .`| \n" +
        "       ,--.'|    ,---,. \\    /  \\            ,----..  |   | :      ,---,    ,---,.       ,--.'|    ,`   .'  : \n" +
        "   ,--,:  : |  ,'  .'  \\|   :    \\          /   /   \\ :   : |   ,`--.' |  ,'  .' |   ,--,:  : |  ;    ;     / \n" +
        ",`--.'`|  ' :,---.' .' ||   |  .\\ :        |   :     :|   ' :   |   :  :,---.'   |,`--.'`|  ' :.'___,/    ,'  \n" +
        "|   :  :  | ||   |  |: |.   :  |: |        .   |  ;. /;   ; '   :   |  '|   |   .'|   :  :  | ||    :     |   \n" +
        ":   |   \\ | ::   :  :  /|   |   \\ :        .   ; /--` '   | |__ |   :  |:   :  |-,:   |   \\ | :;    |.';  ;   \n" +
        "|   : '  '; |:   |    ; |   : .   /        ;   | ;    |   | :.'|'   '  ;:   |  ;/||   : '  '; |`----'  |  |   \n" +
        "'   ' ;.    ;|   :     \\;   | |`-'         |   : |    '   :    ;|   |  ||   :   .''   ' ;.    ;    '   :  ;   \n" +
        "|   | | \\   ||   |   . ||   | ;            .   | '___ |   |  ./ '   :  ;|   |  |-,|   | | \\   |    |   |  '   \n" +
        "'   : |  ; .''   :  '; |:   ' |            '   ; : .'|;   : ;   |   |  ''   :  ;/|'   : |  ; .'    '   :  |   \n" +
        "|   | '`--'  |   |  | ; :   : :            '   | '/  :|   ,/    '   :  ||   |    \\|   | '`--'      ;   |.'    \n" +
        "'   : |      |   :   /  |   | :            |   :    / '---'     ;   |.' |   :   .''   : |          '---'      \n" +
        ";   |.'      |   | ,'   `---'.|             \\   \\ .'            '---'   |   | ,'  ;   |.'                     \n" +
        "'---'        `----'       `---`              `---`                      `----'    '---'                       \n" +
        "                                                                                                              \n" +
        "\n";
  }
}