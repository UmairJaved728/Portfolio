package com.pucit.mobileapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.pucit.mobileapp.activities.HomeScreen;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    LinearLayout loginLayout, signupLayout;
    EditText loginUsername, loginPassword, signupUsername, signupPassword, confirmPassword;
    Spinner spinner;
    Button loginButton, signupButton;
    String name = null, pass = null, confirmPas = null;
    ArrayList<String> usernames = new ArrayList<>();
    ArrayList<String> passwords = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        usernames.add("Umair");
        passwords.add("1234");

        initializeLayouts();
        setupSpinner();
        initializeLoginViews();
        initializeSignupViews();
        setupLoginClickListener();
        setupSignupClickListener();
    }

    void initializeLayouts() {
        spinner = findViewById(R.id.login_signup_spinner);
        loginLayout = findViewById(R.id.login_layout);
        signupLayout = findViewById(R.id.signup_layout);
    }

    void initializeLoginViews() {
        loginUsername = findViewById(R.id.username_login);
        loginPassword = findViewById(R.id.password_login);
        loginButton = findViewById(R.id.button_login);
    }

    void initializeSignupViews() {
        signupUsername = findViewById(R.id.username_signup);
        signupPassword = findViewById(R.id.password_signup);
        confirmPassword = findViewById(R.id.confirm_password_signup);
        signupButton = findViewById(R.id.button_signup);
    }

    void setupSpinner() {
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.login_signup_options, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);

        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                String selectedItem = spinner.getSelectedItem().toString();
                if ("Login".equals(selectedItem)) {
                    // Show the login section and hide the sign-up section
                    initializeLoginViews();
                    loginLayout.setVisibility(View.VISIBLE);
                    signupLayout.setVisibility(View.GONE);
                } else if ("Signup".equals(selectedItem)) {
                    // Show the sign-up section and hide the login section
                    loginLayout.setVisibility(View.GONE);
                    signupLayout.setVisibility(View.VISIBLE);
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
                // by default set the login screen
                initializeSignupViews();
                loginLayout.setVisibility(View.VISIBLE);
                signupLayout.setVisibility(View.GONE);
            }
        });
    }

    void setupLoginClickListener() {
        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                name = loginUsername.getText().toString();
                pass = loginPassword.getText().toString();

                Bundle bundle = new Bundle();
                boolean isValid = name != null && !name.equalsIgnoreCase("") && pass != null && !pass.equalsIgnoreCase("");

                int nameIdx = -1;
                if(isValid) {
                     nameIdx = usernames.indexOf(name);
                }
                // validate
                if(isValid && nameIdx != -1 && pass.equals(passwords.get(nameIdx))) {

                    Log.d("debugLogin", name + " " + pass);

                    Toast.makeText(MainActivity.this, "Hey " + name + "! You are good to go", Toast.LENGTH_SHORT).show();

                    // passing to next page
                    bundle.putString("name", name);
                    Intent intent = new Intent(MainActivity.this, HomeScreen.class);

                    //we can also send data like this =, but only used with primitive types
                    //intent.putExtra(3);
                    // use bundle for any type or key value pairs
                    intent.putExtras(bundle);
                    startActivity(intent);
                    finish();
                } else {
                    loginUsername.setError("Incorrect username");
                    loginPassword.setError("Incorrect password");
                    Log.d("debugLogin", "Can't validate");
                }
            }
        });
    }

    void setupSignupClickListener() {
        signupButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                name = signupUsername.getText().toString();
                pass = signupPassword.getText().toString();
                confirmPas = confirmPassword.getText().toString();

                boolean isValid = name != null && !name.equalsIgnoreCase("") && pass != null && !pass.equalsIgnoreCase("") && confirmPas != null && !confirmPas.equalsIgnoreCase("");

                if(isValid) {
                    if(pass.equals(confirmPas)) {
                        usernames.add(name);
                        passwords.add(pass);

                        Toast.makeText(MainActivity.this, "Account created successfully! You can login now", Toast.LENGTH_SHORT).show();
                        spinner.setSelection(0); // go back to login screen
                    } else {
                        signupPassword.setError("Both passwords should match");
                        confirmPassword.setError("Both passwords should match");
                    }
                } else {
                    signupUsername.setError("Field cannot be empty");
                    signupPassword.setError("Field cannot be empty");
                    confirmPassword.setError("Field cannot be empty");
                    Log.d("debugLogin", "Can't validate");
                }

            }
        });
    }
}