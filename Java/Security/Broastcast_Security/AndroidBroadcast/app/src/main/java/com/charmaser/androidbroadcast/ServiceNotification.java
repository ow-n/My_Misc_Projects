package com.charmaser.androidbroadcast;

import android.app.IntentService;
import android.content.Intent;
import android.util.Log;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

public class ServiceNotification extends IntentService {
    public static boolean ServiceIsRun = false;

    public ServiceNotification() {
        super("MyWebRequestService");
    }

    protected void onHandleIntent(Intent workIntent) {
        // continue sending the messages
        while (ServiceIsRun) {
            // create new intent
            //Intent intent = new Intent();  // implicit intent
            Intent intent = new Intent("com.example.SECURE_BROADCAST"); // explicit intent
            // set the action that will receive our broadcast
            //intent.setAction("com.example.Broadcast"); // overrides SECURE_BROADCAST
            // add data to the bundle
            intent.putExtra("username", "alxs1aa");
            // send the data to broadcast
            //Log.d("ServiceNotification", "sending broadcast");
            //sendBroadcast(intent); // dont broadcast everywhere
            Log.d("ServiceNotification", "sending local broadcast");
            LocalBroadcastManager.getInstance(this).sendBroadcast(intent);
            // delay for 50000ms
            try {
                Thread.sleep(10000);  //10000=10s
            } catch(Exception ex) {}
        }
    }
}