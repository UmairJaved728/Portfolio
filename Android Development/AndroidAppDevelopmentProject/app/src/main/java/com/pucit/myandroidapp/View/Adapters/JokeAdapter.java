package com.pucit.myandroidapp.View.Adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.pucit.myandroidapp.Model.Entities.Joke;
import com.pucit.myandroidapp.R;
import com.pucit.myandroidapp.interfaces.IRecyclerViewData;

import java.util.ArrayList;
import java.util.List;

public class JokeAdapter extends RecyclerView.Adapter<JokeAdapter.JokeViewHolder> {

    private Context context;
    private List<Joke> jokes = new ArrayList<>();
    private IRecyclerViewData data;

    public JokeAdapter(Context context, List<Joke> jokes, IRecyclerViewData data) {
        this.context = context;
        this.jokes = jokes;
        this.data = data;
    }

    public void setJokeList(List<Joke> jokes) {
        this.jokes = jokes;
    }

    @NonNull
    @Override
    public JokeViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.single_joke_item, parent, false);
        return new JokeViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull JokeViewHolder holder, int position) {
        int index = position;
        Joke joke = jokes.get(position);
        holder.jokeType.setText(joke.getType());
        holder.jokeSetup.setText(joke.getSetup());
        holder.jokeLikes.setText("😂 " + joke.getLikes());

        holder.linearLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data.sendData(jokes.get(index));
            }
        });
    }

    @Override
    public int getItemCount() {
        if(jokes == null) {
            return 0;
        }
        return jokes.size();
    }

    static class JokeViewHolder extends RecyclerView.ViewHolder {

        TextView jokeType, jokeSetup, jokePunchline, jokeLikes;
        LinearLayout linearLayout;

        JokeViewHolder(View itemView) {
            super(itemView);
            jokeType = itemView.findViewById(R.id.joke_type);
            jokeSetup = itemView.findViewById(R.id.joke_setup);
            jokePunchline = itemView.findViewById(R.id.joke_punchline);
            linearLayout = itemView.findViewById(R.id.joke_layout);
            jokeLikes = itemView.findViewById(R.id.joke_likes);
        }
    }
}
