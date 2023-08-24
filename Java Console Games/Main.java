1 --------------------------------------

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Integer> arr = new ArrayList<>();
        arr.add(1);
        arr.add(3);
        arr.add(1);
        System.out.println("Array: " + arr);

        int balancedIndex = balancedSum(arr);
        System.out.println("Balanced index: " + balancedIndex);
    }

    public static int balancedSum(List<Integer> arr) {
        int totalSum = 0;
        for (int num : arr) {
            totalSum += num;
        }
        int leftSum = 0;
        for (int i = 0; i < arr.size(); i++) {
            totalSum -= arr.get(i);
            if (leftSum == totalSum) {
                return i;
            }
            leftSum += arr.get(i);
        }
        return -1;
    }

}

2 -------------------------------
/*
Enter your query below.
Please append a semicolon ";" at the end of the query
*/
SELECT c.name, SUM(g.goals) AS goals
FROM Countries c
JOIN Goals g ON c.id = g.country_id
GROUP BY c.id, c.name
ORDER BY goals DESC, c.id ASC;


3 ------------------------------------
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics.CodeAnalysis;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;
using System.Text;
using System;
using System.Net;
using System.Net.Http;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;


class Result
{

    /*
     * Complete the 'getDiscountedPrice' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER barcode as parameter.
     * API URL: https://jsonmock.hackerrank.com/api/inventory?barcode=<barcode>
     */

    public static int getDiscountedPrice(int barcode)
    {
        string apiUrl = $"https://jsonmock.hackerrank.com/api/inventory?barcode={barcode}";
        using (HttpClient client = new HttpClient())
        {
            HttpResponseMessage response = client.GetAsync(apiUrl).Result;
            if (response.IsSuccessStatusCode)
            {
                string responseBody = response.Content.ReadAsStringAsync().Result;
                JObject jsonResponse = JObject.Parse(responseBody);
                JArray dataArray = (JArray)jsonResponse["data"];
                if (dataArray.Count == 1)
                {
                    double price = (double)dataArray[0]["price"];
                    double discount = (double)dataArray[0]["discount"];

                    double discountedPrice = price - ((discount / 100) * price);
                    return (int)Math.Round(discountedPrice);
                }
            }
        }

        return -1;
    }

}

class Solution
{
    public static void Main(string[] args)
    {
        TextWriter textWriter = new StreamWriter(@System.Environment.GetEnvironmentVariable("OUTPUT_PATH"), true);

        int barcode = Convert.ToInt32(Console.ReadLine().Trim());

        int result = Result.getDiscountedPrice(barcode);

        textWriter.WriteLine(result);

        textWriter.Flush();
        textWriter.Close();
    }
}
