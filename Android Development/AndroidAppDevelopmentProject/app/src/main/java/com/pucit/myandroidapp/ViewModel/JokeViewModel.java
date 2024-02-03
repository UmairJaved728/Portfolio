package com.pucit.myandroidapp.ViewModel;

import android.app.Application;
import android.content.Context;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.lifecycle.AndroidViewModel;
import androidx.lifecycle.LiveData;

import com.pucit.myandroidapp.Model.Entities.Joke;
import com.pucit.myandroidapp.Model.Repositories.JokeRepository;
import com.pucit.myandroidapp.R;
import com.pucit.myandroidapp.interfaces.Retro.RequestRetro;
import com.pucit.myandroidapp.utils.AlertDialog;
import com.pucit.myandroidapp.utils.CustomDialog;
import com.pucit.myandroidapp.utils.MainRetro;
import com.pucit.myandroidapp.utils.Notifications;

import java.util.ArrayList;
import java.util.List;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;

public class JokeViewModel extends AndroidViewModel {
    Retrofit retrofit;
    RequestRetro requestRetro;
    JokeRepository jokeRepository;
    Joke randomJoke;
    LiveData<List<Joke>> allJokes;
    ArrayList<Joke> tenRandomJokes;

    public JokeViewModel(@NonNull Application application) {
        super(application);
        retrofit = MainRetro.getInstance();
        requestRetro = retrofit.create(RequestRetro.class);
        jokeRepository = new JokeRepository(application);
        allJokes = jokeRepository.getAllJokes();
    }

    public LiveData<List<Joke>> getAllJokes() {
        return allJokes;
    }

    public void getRandomJoke(Context context) {
        requestRetro.getRandomJoke().enqueue(new Callback<Joke>() {
            @Override
            public void onResponse(@NonNull Call<Joke> call, @NonNull Response<Joke> response) {
                if(response.isSuccessful() && response.body() != null) {
                    randomJoke = response.body();
                    jokeRepository.insertJoke(randomJoke);
                    Notifications.sendNotification(context, "Hurray!", "Your Joke is ready. Come here and checkout your new joke", R.drawable.notifylogo);
                } else {
                    Notifications.sendNotification(context, "OOPS!", "Your Joke cannot be displayed at the moment", R.drawable.notifylogo);
                }
            }

            @Override
            public void onFailure(@NonNull Call<Joke> call, @NonNull Throwable t) {
                Notifications.sendNotification(context, "OOPS!", "Your Joke cannot be displayed at the moment", R.drawable.notifylogo);
            }
        });
    }

    public void getRandomJokeByType(Context context) {
        CustomDialog.show(context, new CustomDialog.DialogListener() {
            @Override
            public void onGeneralClicked() {
                getRandomJokeByTypeHelper(context, "general");
            }

            @Override
            public void onProgrammingClicked() {
                getRandomJokeByTypeHelper(context, "programming");
            }
        });
    }

    private void getRandomJokeByTypeHelper(Context context, String type) {
        requestRetro.getRandomJokeByType(type).enqueue(new Callback<ArrayList<Joke>>() {
            @Override
            public void onResponse(@NonNull Call<ArrayList<Joke>> call, @NonNull Response<ArrayList<Joke>> response) {
                if(response.isSuccessful() && response.body() != null) {
                    randomJoke = response.body().get(0);
                    jokeRepository.insertJoke(randomJoke);
                    Notifications.sendNotification(context, "Hurray!", "Your Joke is ready. Come here and checkout your new joke", R.drawable.notifylogo);
                } else {
                    Notifications.sendNotification(context, "OOPS!", "Your Joke cannot be displayed at the moment", R.drawable.notifylogo);
                }
            }

            @Override
            public void onFailure(@NonNull Call<ArrayList<Joke>> call, @NonNull Throwable t) {
                Notifications.sendNotification(context, "OOPS!", "Your Joke cannot be displayed at the moment", R.drawable.notifylogo);
            }
        });
    }

    public void getTenRandomJokes(Context context) {
        CustomDialog.show(context, new CustomDialog.DialogListener() {
            @Override
            public void onGeneralClicked() {
                getTenRandomJokesHelper(context, "general");
            }

            @Override
            public void onProgrammingClicked() {
                getTenRandomJokesHelper(context, "programming");
            }
        });
    }

    private void getTenRandomJokesHelper(Context context, String type) {
        requestRetro.getTenRandomJokesByType(type).enqueue(new Callback<ArrayList<Joke>>() {
            @Override
            public void onResponse(@NonNull Call<ArrayList<Joke>> call, @NonNull Response<ArrayList<Joke>> response) {
                if(response.isSuccessful() && response.body() != null) {
                    tenRandomJokes = response.body();
                    jokeRepository.insertAllJokes(tenRandomJokes);
                    Notifications.sendNotification(context, "Hurray!", "Your 10 Jokes are ready. Come here and checkout your new jokes", R.drawable.notifylogo);
                } else {
                    Notifications.sendNotification(context, "OOPS!", "Your Jokes cannot be displayed at the moment", R.drawable.notifylogo);
                }
            }

            @Override
            public void onFailure(@NonNull Call<ArrayList<Joke>> call, @NonNull Throwable t) {
                Notifications.sendNotification(context, "OOPS!", "Your Jokes cannot be displayed at the moment", R.drawable.notifylogo);
            }
        });
    }

    public void handleJokeItemClick(Context context, Joke joke) {
        AlertDialog.show(context, joke.getPunchline(), new AlertDialog.DialogListener() {
            @Override
            public void onPositiveButtonClicked() {
                jokeRepository.incrementLikes(joke);
            }

            @Override
            public void onNegativeButtonClicked() {
                jokeRepository.deleteJoke(joke);
            }
        });
    }
}
