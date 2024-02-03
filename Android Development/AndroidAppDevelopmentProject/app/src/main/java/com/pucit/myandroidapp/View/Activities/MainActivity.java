package com.pucit.myandroidapp.View.Activities;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import com.pucit.myandroidapp.Model.models.User;
import com.pucit.myandroidapp.R;
import com.pucit.myandroidapp.databinding.ActivityMainBinding;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    ActivityMainBinding xml;
    String name = null, pass = null, confirmPas = null;
    ArrayList<User> users = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        xml = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(xml.getRoot());

        User admin = new User("umair", "1234");
        users.add(admin);

        setupSpinner();
        setupLoginClickListener();
        setupSignupClickListener();
    }

    void setupSpinner() {
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.login_signup_options, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        xml.loginSignupSpinner.setAdapter(adapter);

        xml.loginSignupSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                String selectedItem = xml.loginSignupSpinner.getSelectedItem().toString();
                if ("Login".equals(selectedItem)) {
                    // Show the login section and hide the sign-up section
                    xml.loginLayout.setVisibility(View.VISIBLE);
                    xml.signupLayout.setVisibility(View.GONE);
                } else if ("Signup".equals(selectedItem)) {
                    // Show the sign-up section and hide the login section
                    xml.loginLayout.setVisibility(View.GONE);
                    xml.signupLayout.setVisibility(View.VISIBLE);
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
                // by default set the login screen
                xml.loginLayout.setVisibility(View.VISIBLE);
                xml.signupLayout.setVisibility(View.GONE);
            }
        });
    }

    void setupLoginClickListener() {
        xml.buttonLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                name = xml.usernameLogin.getText().toString();
                pass = xml.passwordLogin.getText().toString();

                Bundle bundle = new Bundle();
                boolean isValid = name != null && !name.equalsIgnoreCase("") && pass != null && !pass.equalsIgnoreCase("");

                int nameIdx = -1;
                if(isValid) {
                    isValid = false;
                    for (int i=0; i<users.size(); i++) {
                        if (users.get(i).getUsername().equals(name) && users.get(i).getPassword().equals(pass)) {
                            isValid = true;
                            break;
                        }
                    }
                }
                // validate
                if(isValid) {

                    Log.d("debugLogin", name + " " + pass);

                    Toast.makeText(MainActivity.this, "Hey " + name + "! You are good to go", Toast.LENGTH_SHORT).show();

                    // passing to next page
                    bundle.putString("name", name);
                    Intent intent = new Intent(MainActivity.this, HomeScreenActivity.class);

                    //we can also send data like this =, but only used with primitive types
                    //intent.putExtra(3);
                    // use bundle for any type or key value pairs
                    intent.putExtras(bundle);
                    startActivity(intent);
                    finish();
                } else {
                    xml.usernameLogin.setError("Incorrect username");
                    xml.passwordLogin.setError("Incorrect password");
                    Log.d("debugLogin", "Can't validate");
                }
            }
        });

        xml.signupText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                xml.loginSignupSpinner.setSelection(1);
            }
        });
    }

    void setupSignupClickListener() {
        xml.buttonSignup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                name = xml.usernameSignup.getText().toString();
                pass = xml.passwordSignup.getText().toString();
                confirmPas = xml.confirmPasswordSignup.getText().toString();

                boolean isValid = name != null && !name.equalsIgnoreCase("") && pass != null && !pass.equalsIgnoreCase("") && confirmPas != null && !confirmPas.equalsIgnoreCase("");

                if (isValid) {
                    if (pass.equals(confirmPas)) {
                        User user = new User(name, pass);
                        users.add(user);

                        Toast.makeText(MainActivity.this, "Account created successfully! You can login now", Toast.LENGTH_SHORT).show();
                        xml.loginSignupSpinner.setSelection(0); // go back to login screen
                    } else {
                        xml.passwordSignup.setError("Both passwords should match");
                        xml.confirmPasswordSignup.setError("Both passwords should match");
                    }
                } else {
                    xml.usernameSignup.setError("Field cannot be empty");
                    xml.passwordSignup.setError("Field cannot be empty");
                    xml.confirmPasswordSignup.setError("Field cannot be empty");
                    Log.d("debugLogin", "Can't validate");
                }

            }
        });

        xml.loginText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                xml.loginSignupSpinner.setSelection(0);
            }
        });
    }
}