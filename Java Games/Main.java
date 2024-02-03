/*
 * Question 1
 */
import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;



class Result {

    /*
     * Complete the 'balancedSum' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER_ARRAY arr as parameter.
     */

    public static int balancedSum(List<Integer> arr) {
        int sum = 0, lSum = 0, i, n;
        for(i = 0; i < arr.size(); i++)
        {
            sum += arr.get(i);
        }
        
        for(i = 0; i < arr.size(); i++)
        {
            n = arr.get(i);
            sum -= n;
            if(sum == lSum)
                return i;
            lSum += n;
        }
        return -9;
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int arrCount = Integer.parseInt(bufferedReader.readLine().trim());

        List<Integer> arr = IntStream.range(0, arrCount).mapToObj(i -> {
            try {
                return bufferedReader.readLine().replaceAll("\\s+$", "");
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        })
            .map(String::trim)
            .map(Integer::parseInt)
            .collect(toList());

        int result = Result.balancedSum(arr);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
/*
 * Question 2
 */
/*
Enter your query below.
Please append a semicolon ";" at the end of the query
*/
SELECT c.name, SUM(g.goals) AS goals
FROM Countries c
JOIN Goals g ON c.id = g.country_id
GROUP BY c.id, c.name
ORDER BY goals DESC, c.id ASC;


/*
 * Question 3
 */
import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.function.*;
import java.util.regex.*;
import java.util.stream.*;
import static java.util.stream.Collectors.joining;
import static java.util.stream.Collectors.toList;
import java.net.*;
import org.json.simple.*;
import org.json.simple.parser.*;



class Result {

    /*
     * Complete the 'getDiscountedPrice' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER barcode as parameter.
     * API URL: https://jsonmock.hackerrank.com/api/inventory?barcode=<barcode>
     */

    public static int getDiscountedPrice(int barcode) {
        try {
            URL url = new URL("https://jsonmock.hackerrank.com/api/inventory?barcode=" + barcode);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");

            BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String line;
            StringBuilder response = new StringBuilder();

            while ((line = reader.readLine()) != null) {
                response.append(line);
            }
            reader.close();

            JSONParser parser = new JSONParser();
            JSONObject jsonResponse = (JSONObject) parser.parse(response.toString());
            JSONArray dataArray = (JSONArray) jsonResponse.get("data");

            if (dataArray.size() != 1) {
                return -1;
            }
            
            JSONObject item = (JSONObject) dataArray.get(0);
            double price = (long) item.get("price");
            double discount = (long) item.get("discount");
            double discountedPrice = price - ((discount / 100.0) * price);
            return (int) Math.round(discountedPrice);
        } catch (Exception e) {
            return -1;
        }
    }

}

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int barcode = Integer.parseInt(bufferedReader.readLine().trim());

        int result = Result.getDiscountedPrice(barcode);

        bufferedWriter.write(String.valueOf(result));
        bufferedWriter.newLine();

        bufferedReader.close();
        bufferedWriter.close();
    }
}
