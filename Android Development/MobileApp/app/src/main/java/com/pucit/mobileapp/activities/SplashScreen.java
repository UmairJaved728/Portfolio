package com.pucit.mobileapp.activities;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

import com.pucit.mobileapp.MainActivity;
import com.pucit.mobileapp.R;

@SuppressLint("CustomSplashScreen")
public class SplashScreen extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash_screen);

        // add delay

        // option 1
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                // this function will execute after 5000 milliseconds (5 seconds)
                Intent intent = new Intent(SplashScreen.this, MainActivity.class);
                startActivity(intent);
                finish();       // removes from stack
            }
        }, 3000);

//          option 2
//        new CountDownTimer(5000, 5000) {
//            @Override
//            public void onTick(long l) {
//                // runs every second
//            }
//
//            @Override
//            public void onFinish() {
//                // runs after given time (here 5 seconds)
//                Intent intent = new Intent(SplashScreen.this, MainActivity.class);
//                startActivity(intent);
//            }
//        };
    }
}