package com.pucit.myandroidapp.utils;

import android.app.Dialog;
import android.content.Context;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;

import com.pucit.myandroidapp.R;

public class CustomDialog {
    public interface DialogListener {
        void onGeneralClicked();
        void onProgrammingClicked();
    }

    public static void show(Context context, DialogListener listener) {
        Dialog dialog = new Dialog(context);
        dialog.setContentView(R.layout.custom_dialog);

        //sticking to screen
        dialog.setCancelable(true);

        Window window = dialog.getWindow();

        // Set fixed width for the dialog window
        WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams();
        assert window != null;
        layoutParams.copyFrom(window.getAttributes());
        window.setAttributes(layoutParams);

        // Initialize buttons from the dialog layout
        Button generalButton = dialog.findViewById(R.id.generalButton);
        Button programmingButton = dialog.findViewById(R.id.programmingButton);

        // Set click listeners for the buttons
        generalButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Call the listener method for "General" option
                if (listener != null) {
                    listener.onGeneralClicked();
                }
                dialog.dismiss();
            }
        });

        programmingButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Call the listener method for "Programming" option
                if (listener != null) {
                    listener.onProgrammingClicked();
                }
                dialog.dismiss();
            }
        });

        dialog.show();
    }
}
