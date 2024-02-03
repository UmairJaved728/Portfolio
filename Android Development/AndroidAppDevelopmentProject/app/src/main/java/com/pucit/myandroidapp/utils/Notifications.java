package com.pucit.myandroidapp.utils;

import static android.content.Context.NOTIFICATION_SERVICE;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;

import androidx.core.content.ContextCompat;
import androidx.core.content.res.ResourcesCompat;

import com.pucit.myandroidapp.R;

public class Notifications {

    private static final String CHANNEL_ID = "124564";
    private static final int NOTIFICATION_ID = 100;

    public static Drawable getDrawableFromDrawableFolder(Context context, int drawableResourceId) {
        return ContextCompat.getDrawable(context, drawableResourceId);
    }
    public static void sendNotification(Context context, String title, String message, int img) {

        // converting from int to drawable
        Drawable drawable = getDrawableFromDrawableFolder(context, img);

        // converting to bitmap
        BitmapDrawable bitmapDrawable = (BitmapDrawable) drawable;
        Bitmap largeIcon = bitmapDrawable.getBitmap();

        // getting access via manager
        NotificationManager notificationManager =
                (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        Notification notification;

        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {

            //before Oreo
            //// main title will be app name, subtext will be custom title
            notification = new Notification.Builder(context)
                    .setLargeIcon(largeIcon)
                    .setSmallIcon(img)
                    .setContentText(message)
                    .setSubText(title)
                    .setChannelId(Notifications.CHANNEL_ID)
                    .build();
            notificationManager.createNotificationChannel(new NotificationChannel(CHANNEL_ID, "New Channel", NotificationManager.IMPORTANCE_HIGH));
        } else {
            // after oreo
            notification = new Notification.Builder(context)
                    .setLargeIcon(largeIcon)
                    .setSmallIcon(img)
                    .setContentText(message)
                    .setSubText(title)
                    .build();
        }

        notificationManager.notify(NOTIFICATION_ID, notification);
    }
}
