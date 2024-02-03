package com.pucit.mobileapp.activities;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import android.os.Bundle;

import com.pucit.mobileapp.R;
import com.pucit.mobileapp.fragments.FragmentOne;
import com.pucit.mobileapp.fragments.FragmentTwo;

public class FragmentsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fragments);

        Fragment fragmentOne = new FragmentOne();
        FragmentTransaction fragmentTransaction = getSupportFragmentManager().beginTransaction();

        // fragmentTransaction.add(R.id.frame1, fragmentOne); // add to stack
        fragmentTransaction.replace(R.id.frame1, fragmentOne);     // remove current fragment from stack and add this

        // when the back button is clicked
        fragmentTransaction.addToBackStack(null);

        // fragement is visible
        fragmentTransaction.commit();

        Fragment fragmentTwo = new FragmentTwo();
        FragmentTransaction fragmentTransaction1 = getSupportFragmentManager().beginTransaction();

        // fragmentTransaction.add(R.id.frame1, fragmentOne); // add to stack
        fragmentTransaction1.replace(R.id.frame2, fragmentTwo);     // remove current fragment from stack and add this

        // when the back button is clicked
        fragmentTransaction1.addToBackStack(null);

        // fragement is visible
        fragmentTransaction1.commit();
    }
}