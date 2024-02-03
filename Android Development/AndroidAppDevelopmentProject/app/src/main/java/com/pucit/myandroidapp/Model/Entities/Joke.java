package com.pucit.myandroidapp.Model.Entities;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.Ignore;
import androidx.room.PrimaryKey;

import com.pucit.myandroidapp.Model.models.User;

@Entity(tableName = "joke")
public class Joke {
    @PrimaryKey(autoGenerate = true)
    private int id;

    @ColumnInfo
    private String type;

    @ColumnInfo
    private String setup;

    @ColumnInfo
    private String punchline;

    @ColumnInfo(defaultValue = "0")
    private int likes;

    public Joke(int id, String type, String setup, String punchline) {
        this.id = id;
        this.type = type;
        this.setup = setup;
        this.punchline = punchline;
    }

    public int getLikes() {
        return likes;
    }

    public void setLikes(int likes) {
        this.likes = likes;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getSetup() {
        return setup;
    }

    public void setSetup(String setup) {
        this.setup = setup;
    }

    public String getPunchline() {
        return punchline;
    }

    public void setPunchline(String punchline) {
        this.punchline = punchline;
    }
}
