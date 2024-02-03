package com.pucit.myandroidapp.View.Activities;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;

import com.pucit.myandroidapp.View.Adapters.JokeAdapter;
import com.pucit.myandroidapp.Model.Entities.Joke;
import com.pucit.myandroidapp.R;
import com.pucit.myandroidapp.ViewModel.JokeViewModel;
import com.pucit.myandroidapp.interfaces.IRecyclerViewData;

import java.util.ArrayList;
import java.util.List;

public class RecyclerViewActivity extends AppCompatActivity implements IRecyclerViewData {

    private RecyclerView recyclerView;
    private JokeAdapter adapter;
    private LiveData<List<Joke>> jokeList;
    JokeViewModel jokeViewModel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recycler_view);

        recyclerView = findViewById(R.id.recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        jokeViewModel = new ViewModelProvider(this).get(JokeViewModel.class);
        jokeList = jokeViewModel.getAllJokes();

        adapter = new JokeAdapter(RecyclerViewActivity.this, jokeList.getValue(), this);
        recyclerView.setAdapter(adapter);

        jokeList.observe(this, jokes -> {
            adapter.setJokeList(jokes);
            recyclerView.setLayoutManager(new LinearLayoutManager(this));
            recyclerView.setAdapter(adapter);
        });
    }

    @Override
    public void sendData(Joke joke) {
        jokeViewModel.handleJokeItemClick(RecyclerViewActivity.this, joke);
    }
}