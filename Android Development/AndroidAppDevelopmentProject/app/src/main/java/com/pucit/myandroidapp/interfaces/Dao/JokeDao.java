package com.pucit.myandroidapp.interfaces.Dao;

import androidx.lifecycle.LiveData;
import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.OnConflictStrategy;
import androidx.room.Query;

import com.pucit.myandroidapp.Model.Entities.Joke;

import java.util.List;

@Dao
public interface JokeDao {
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    void insertJoke(Joke joke);

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    void insertAllJokes(List<Joke> jokes);

    @Query("SELECT * FROM joke")
    LiveData<List<Joke>> getAllJokes();

    @Delete
    void deleteJoke(Joke joke);

    @Query("UPDATE joke SET likes = likes + 1 WHERE id = :jokeId")
    void incrementLikes(int jokeId);
}
