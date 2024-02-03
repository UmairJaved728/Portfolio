package com.pucit.myandroidapp.View.Activities;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import com.pucit.myandroidapp.databinding.ActivityCalculatorBinding;

public class CalculatorActivity extends AppCompatActivity {

    ActivityCalculatorBinding xml;
    private String currentInput = "";
    private double firstOperand = 0;
    private String currentOperation = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        xml = ActivityCalculatorBinding.inflate(getLayoutInflater());
        setContentView(xml.getRoot());

        setupButtonListeners();
    }

    private void setupButtonListeners() {
        // Numeric buttons
        xml.btn0.setOnClickListener(view -> appendNumber("0"));
        xml.btn1.setOnClickListener(view -> appendNumber("1"));
        xml.btn2.setOnClickListener(view -> appendNumber("2"));
        xml.btn3.setOnClickListener(view -> appendNumber("3"));
        xml.btn4.setOnClickListener(view -> appendNumber("4"));
        xml.btn5.setOnClickListener(view -> appendNumber("5"));
        xml.btn6.setOnClickListener(view -> appendNumber("6"));
        xml.btn7.setOnClickListener(view -> appendNumber("7"));
        xml.btn8.setOnClickListener(view -> appendNumber("8"));
        xml.btn9.setOnClickListener(view -> appendNumber("9"));


        // Operations
        xml.btnAdd.setOnClickListener(view -> setOperation("+"));
        xml.btnMinus.setOnClickListener(view -> setOperation("-"));
        xml.btnMultiply.setOnClickListener(view -> setOperation("*"));
        xml.btnDivide.setOnClickListener(view -> setOperation("/"));

        // Equal, Clear, Delete, Dot, Sign change
        xml.btnEqual.setOnClickListener(view -> calculateResult());
        xml.btnAC.setOnClickListener(view -> clearInput());
        xml.btnDEL.setOnClickListener(view -> deleteLastCharacter());
        xml.btnDot.setOnClickListener(view -> appendDot());
        xml.btnSign.setOnClickListener(view -> toggleSign());
    }

    private void appendNumber(String number) {
        currentInput += number;
        updateDisplay();
    }

    private void setOperation(String operation) {
        if (!currentInput.isEmpty()) {
            firstOperand = Double.parseDouble(currentInput);
            currentOperation = operation;
            currentInput = "";
        }
    }

    private void calculateResult() {
        if (currentOperation != null && !currentInput.isEmpty()) {
            double secondOperand = Double.parseDouble(currentInput);
            double result = 0;
            switch (currentOperation) {
                case "+":
                    result = firstOperand + secondOperand;
                    break;
                case "-":
                    result = firstOperand - secondOperand;
                    break;
                case "*":
                    result = firstOperand * secondOperand;
                    break;
                case "/":
                    if (secondOperand != 0) {
                        result = firstOperand / secondOperand;
                    } else {
                        xml.textView.setText("Error");
                        return;
                    }
                    break;
            }
            currentInput = String.valueOf(result);
            updateDisplay();
            currentOperation = null;
        }
    }

    private void clearInput() {
        currentInput = "";
        updateDisplay();
    }

    private void deleteLastCharacter() {
        if (!currentInput.isEmpty()) {
            currentInput = currentInput.substring(0, currentInput.length() - 1);
            updateDisplay();
        }
    }

    private void appendDot() {
        if (!currentInput.contains(".")) {
            currentInput += ".";
            updateDisplay();
        }
    }

    private void toggleSign() {
        if (!currentInput.isEmpty() && !currentInput.equals("0")) {
            if (currentInput.startsWith("-")) {
                currentInput = currentInput.substring(1);
            } else {
                currentInput = "-" + currentInput;
            }
            updateDisplay();
        }
    }

    private void updateDisplay() {
        xml.textView.setText(currentInput.isEmpty() ? "0" : currentInput);
    }
}
