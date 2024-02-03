package com.pucit.mobileapp.activities;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.BroadcastReceiver;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.PersistableBundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.pucit.mobileapp.R;

public class HomeScreen extends AppCompatActivity {

    TextView dataTextView;
    Bundle bundle = null;

    Button buttonRV, buttonFA, buttonCalculator;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_screen);

        Log.d("lifecycle", "onCreate()");
        dataTextView = findViewById(R.id.recievedData);
        buttonRV = findViewById(R.id.btnRecycler);
        buttonFA = findViewById(R.id.btnFragment);
        buttonCalculator = findViewById(R.id.btnCalculator);

        bundle = getIntent().getExtras();
        assert bundle != null;
        String name = bundle.getString("name", "default");
        String text = "Welcome " + name + "!";

        dataTextView.setText(text);

        buttonRV.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(HomeScreen.this, RecyclerViewActivity.class);
                startActivity(intent);
            }
        });

        buttonFA.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(HomeScreen.this, FragmentsActivity.class);
                startActivity(intent);
            }
        });

        buttonCalculator.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(HomeScreen.this, CalculatorActivity.class);
                startActivity(intent);
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d("lifecycle", "onStart()");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d("lifecycle", "onResume()");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d("lifecycle", "onPause()");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d("lifecycle", "onStop()");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d("lifecycle", "onDestroy()");
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putString("data", "Saved String");
        Log.d("lifecycle", "onSaveInstanceState()");
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        String text = savedInstanceState.getString("data");
        Log.d("lifecycle", "onRestoreInstanceState()");
    }

    @Override
    public void onRestoreInstanceState(@Nullable Bundle savedInstanceState, @Nullable PersistableBundle persistentState) {
        super.onRestoreInstanceState(savedInstanceState, persistentState);
        assert savedInstanceState != null;
        String text = savedInstanceState.getString("data");
        Log.d("lifecycle", "onRestoreInstanceState()");
    }
}