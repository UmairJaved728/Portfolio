package com.pucit.myandroidapp.Model.Repositories;

import android.app.Application;
import androidx.lifecycle.LiveData;
import com.pucit.myandroidapp.Model.Databases.JokeRoomDatabase;
import com.pucit.myandroidapp.Model.Entities.Joke;
import com.pucit.myandroidapp.interfaces.Dao.JokeDao;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class JokeRepository {
    private JokeRoomDatabase jokeRoomDatabase;
    private JokeDao jokeDao;
    private ExecutorService executorService;
    LiveData<List<Joke>> allJokes;

    public JokeRepository(Application application) {
        jokeRoomDatabase = JokeRoomDatabase.getInstance(application);
        jokeDao = jokeRoomDatabase.jokeDao();
        executorService = Executors.newSingleThreadExecutor();
        allJokes = jokeDao.getAllJokes();
    }

    public void insertJoke(final Joke joke) {
        executorService.execute(new Runnable() {
            @Override
            public void run() {
                jokeDao.insertJoke(joke);
            }
        });
    }

    public void insertAllJokes(final List<Joke> jokes) {
        executorService.execute(new Runnable() {
            @Override
            public void run() {
                jokeDao.insertAllJokes(jokes);
            }
        });
    }

    public void deleteJoke(final Joke joke) {
        executorService.execute(new Runnable() {
            @Override
            public void run() {
                jokeDao.deleteJoke(joke);
            }
        });
    }

    public LiveData<List<Joke>> getAllJokes() {
        return allJokes;
    }

    public void incrementLikes(final Joke joke){
        executorService.execute(new Runnable() {
            @Override
            public void run() {
                jokeDao.incrementLikes(joke.getId());
            }
        });
    }
}
