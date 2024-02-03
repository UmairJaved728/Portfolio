package com.pucit.myandroidapp.utils;

import android.content.Context;
import android.content.DialogInterface;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;

public class AlertDialog {
    public interface DialogListener {
        void onPositiveButtonClicked();
        void onNegativeButtonClicked();
    }

    public static void show(Context context, String message, DialogListener callbacks) {
        MaterialAlertDialogBuilder builder = new MaterialAlertDialogBuilder(context);
        builder.setTitle("Punchline");
        builder.setMessage(message);
        builder.setPositiveButton("Haha 😂", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                callbacks.onPositiveButtonClicked();
            }
        });

        builder.setNegativeButton("Delete it 😒", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                callbacks.onNegativeButtonClicked();
            }
        });

        builder.show();
    }
}
