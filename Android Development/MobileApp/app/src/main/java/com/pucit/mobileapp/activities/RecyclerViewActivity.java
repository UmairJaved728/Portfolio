package com.pucit.mobileapp.activities;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.pucit.mobileapp.R;
import com.pucit.mobileapp.adapter.RVListAdapter;
import com.pucit.mobileapp.models.ListItemModel;

import java.util.ArrayList;

public class RecyclerViewActivity extends AppCompatActivity {

    TextView title;
    RecyclerView recyclerViewlist;

    ArrayList<ListItemModel> listData = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recycler_view);

        initialize();
        // populate list
        populateList();

        RVListAdapter adapter = new RVListAdapter(this, listData);
        recyclerViewlist.setAdapter(adapter);
    }

    private void initialize() {
        // initialize views
        title = findViewById(R.id.textviewTitle);
        recyclerViewlist = findViewById(R.id.recyclerViewList);
        recyclerViewlist.setLayoutManager(new LinearLayoutManager(this));
    }

    private void populateList() {
        if (listData==null || listData.isEmpty()){

            listData.add(new ListItemModel(R.drawable.logo_1, "Umair", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_2, "ALi", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_3, "Fatima", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_4, "Bilal", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_3, "Umair", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_2, "Ali", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_1, "Umar", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_2, "Asad", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_1, "Umair", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_2, "ALi", "A student of CS"));
            listData.add(new ListItemModel(R.drawable.logo_3, "Fatima", "A student of CS"));
        }


    }
}
