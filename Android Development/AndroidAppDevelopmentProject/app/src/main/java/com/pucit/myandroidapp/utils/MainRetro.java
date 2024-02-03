package com.pucit.myandroidapp.utils;

import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class MainRetro {
    private static final String BASE_URL = "https://official-joke-api.appspot.com/jokes/";
    private static Retrofit retrofit = null;

    private MainRetro() {}

    public static Retrofit getInstance() {
        if (retrofit == null) {
            synchronized (MainRetro.class) {
                if(retrofit == null) {
                    retrofit = new Retrofit.Builder()
                            .baseUrl(BASE_URL)
                            .addConverterFactory(GsonConverterFactory.create())
                            .build();
                }
            }
        }

        return retrofit;
    }
}
