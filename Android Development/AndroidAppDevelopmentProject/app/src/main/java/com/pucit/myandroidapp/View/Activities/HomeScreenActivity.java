package com.pucit.myandroidapp.View.Activities;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.pucit.myandroidapp.R;
import com.pucit.myandroidapp.ViewModel.JokeViewModel;
import com.pucit.myandroidapp.databinding.ActivityHomeScreenBinding;
import com.pucit.myandroidapp.utils.Notifications;

public class HomeScreenActivity extends AppCompatActivity {

    ActivityHomeScreenBinding xml;
    JokeViewModel jokeViewModel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        xml = ActivityHomeScreenBinding.inflate(getLayoutInflater());
        setContentView(xml.getRoot());
        jokeViewModel = new ViewModelProvider(this).get(JokeViewModel.class);
        handleCalculatorClick();
        setupGetRandomJoke();
        setupGetRandomJokeByType();
        setupGetTenRandomJokes();
        setupViewAllJokes();
    }

    private void handleCalculatorClick() {
        xml.calculatorBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(HomeScreenActivity.this, CalculatorActivity.class);
                startActivity(intent);
            }
        });
    }

    private void setupGetRandomJoke() {
        xml.randomJokeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jokeViewModel.getRandomJoke(HomeScreenActivity.this);
            }
        });
    }

    private void setupGetRandomJokeByType() {
        xml.randomJokeByTypeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                jokeViewModel.getRandomJokeByType(HomeScreenActivity.this);
            }
        });
    }

    private void setupGetTenRandomJokes() {
        xml.tenRandomJokesBtn.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View v) {
                jokeViewModel.getTenRandomJokes(HomeScreenActivity.this);
            }
        });
    }

    private void setupViewAllJokes() {
        xml.allJokesBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(HomeScreenActivity.this, RecyclerViewActivity.class);
                //The startActivity method is called with the Intent, indicating that the MainActivity is going to be started.
                startActivity(intent);
            }
        });
    }
}