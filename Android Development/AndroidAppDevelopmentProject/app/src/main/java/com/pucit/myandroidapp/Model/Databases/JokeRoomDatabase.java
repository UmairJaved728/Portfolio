package com.pucit.myandroidapp.Model.Databases;

import android.content.Context;

import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;
import com.pucit.myandroidapp.Model.Entities.Joke;
import com.pucit.myandroidapp.interfaces.Dao.JokeDao;

@Database(entities = {Joke.class}, version = 1, exportSchema = false)
public abstract class JokeRoomDatabase extends RoomDatabase {

    public static final String DATABASE_NAME="JokeRoomDatabase";
    public abstract JokeDao jokeDao();
    private static volatile JokeRoomDatabase INSTANCE;

    public static JokeRoomDatabase getInstance(final Context context) {
        if (INSTANCE == null) {
            synchronized (JokeRoomDatabase.class) {
                if (INSTANCE == null) {
                    INSTANCE = Room.databaseBuilder(context,
                                    JokeRoomDatabase.class, DATABASE_NAME)
                            .build();
                }
            }
        }
        return INSTANCE;
    }
}
