package com.pucit.mobileapp.activities;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.pucit.mobileapp.MainActivity;
import com.pucit.mobileapp.R;

public class CalculatorActivity extends AppCompatActivity {
    private TextView display;
    private double operand1 = Double.NaN;
    private double operand2 = Double.NaN;
    private String operator = "";
    Button one, two, three, four, five, six, seven, eight, nine, zero, dot, plus, minus, multiply, divide, equals;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_calculator);
        initializeViews();
        addOnClickListeners();
    }

    void initializeViews() {
        display = findViewById(R.id.display);
        display.setText("");
        one = findViewById(R.id.one);
        two = findViewById(R.id.two);
        three = findViewById(R.id.three);
        four = findViewById(R.id.four);
        five = findViewById(R.id.five);
        six = findViewById(R.id.six);
        seven = findViewById(R.id.seven);
        eight = findViewById(R.id.eight);
        nine = findViewById(R.id.nine);
        zero = findViewById(R.id.zero);
        dot = findViewById(R.id.dot);
        plus = findViewById(R.id.plus);
        minus = findViewById(R.id.minus);
        multiply = findViewById(R.id.multiply);
        divide = findViewById(R.id.divide);
        equals = findViewById(R.id.equals);
    }

    void addOnClickListeners() {
        zero.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("0");
            }
        });

        one.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("1");
            }
        });

        two.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("2");
            }
        });

        three.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("3");
            }
        });

        four.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("4");
            }
        });

        five.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("5");
            }
        });

        six.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("6");
            }
        });

        seven.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("7");
            }
        });

        eight.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("8");
            }
        });

        nine.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay("9");
            }
        });

        dot.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                appendTextToDisplay(".");
            }
        });

        plus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handleOperator("+");
            }
        });

        minus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handleOperator("-");
            }
        });

        multiply.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handleOperator("*");
            }
        });

        divide.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handleOperator("/");
            }
        });

        equals.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                calculateResult();
            }
        });
    }

    private void appendTextToDisplay(String value) {
        display.setText(String.format("%s%s", display.getText().toString(), value));
    }

    private void handleOperator(String newOperator) {
        if (!Double.isNaN(operand1)) {
            calculateResult();
            operand2 = parseDouble(display.getText().toString());
        } else {
            operand1 = parseDouble(display.getText().toString());
        }
        operator = newOperator;
        display.setText("");
    }

    private void calculateResult() {
        if (!Double.isNaN(operand1) && !operator.isEmpty()) {
            operand2 = parseDouble(display.getText().toString());
            double result = 0.0;

            switch (operator) {
                case "+":
                    result = operand1 + operand2;
                    break;
                case "-":
                    result = operand1 - operand2;
                    break;
                case "*":
                    result = operand1 * operand2;
                    break;
                case "/":
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        display.setText(R.string.error);
                        return;
                    }
                    break;
            }

            display.setText(String.valueOf(result));
            operand1 = result;
            operator = "";
        }
    }

    private double parseDouble(String str) {
        double n = Double.NaN;
        try {
            n = Double.parseDouble(str);
        } catch (Exception e) {
            display.setText(R.string.error);
            operand1 = Double.NaN;
            operand2 = Double.NaN;
            operator = "";
            Toast.makeText(CalculatorActivity.this, "Invalid Number!!", Toast.LENGTH_SHORT).show();
        }

        return n;
    }
}
