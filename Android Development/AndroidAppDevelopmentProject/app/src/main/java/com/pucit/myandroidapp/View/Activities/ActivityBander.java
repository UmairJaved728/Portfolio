package com.pucit.myandroidapp.View.Activities;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;

import android.os.Bundle;
import android.view.View;

import com.pucit.myandroidapp.R;
import com.pucit.myandroidapp.databinding.ActivityBanderBinding;

public class ActivityBander extends AppCompatActivity {

    ActivityBanderBinding dataBinder;
    ActivityBanderBinding xml;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // View Binding
        xml = ActivityBanderBinding.inflate(getLayoutInflater());
        setContentView(xml.getRoot());

        // Data Binding
        dataBinder = DataBindingUtil.setContentView(this, R.layout.activity_bander);

        dataBinder.khotaButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String text = dataBinder.khotaInput.getText().toString();
                dataBinder.setMyKhotaText(text);
            }
        });

    }
}