package com.charmaser.androidbroadcast;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class MyReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        Log.d("MyReceiver", "MyReceiver");
        // get the bundles in the message
        final Bundle bundle = intent.getExtras();
        // check the action equal to the action we fire in broadcast,
//        if (intent.getAction().equalsIgnoreCase("com.example.Broadcast"))
//            // read the data from the intent
//            Toast.makeText(context, bundle.getString("username"),Toast.LENGTH_LONG).show();
        // check action is secure
        if (intent.getAction().equals("com.example.SECURE_BROADCAST")) {
            Toast.makeText(context, bundle.getString("username"), Toast.LENGTH_LONG).show();
        }
    }
}