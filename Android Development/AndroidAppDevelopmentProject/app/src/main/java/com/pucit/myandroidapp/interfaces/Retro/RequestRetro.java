package com.pucit.myandroidapp.interfaces.Retro;

import com.pucit.myandroidapp.Model.Entities.Joke;

import java.util.ArrayList;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Path;
import retrofit2.http.Query;

public interface RequestRetro {
    @GET("random")
    Call<Joke> getRandomJoke();

    @GET("{type}/random")
    Call<ArrayList<Joke>> getRandomJokeByType(@Path("type") String jokeType);

    @GET("{type}/ten")
    Call<ArrayList<Joke>> getTenRandomJokesByType(@Path("type") String jokeType);
}
