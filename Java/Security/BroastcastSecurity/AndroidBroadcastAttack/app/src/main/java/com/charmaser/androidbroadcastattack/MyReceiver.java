package com.charmaser.androidbroadcastattack;

import android.app.Notification;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class MyReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        String dataBundel = "";
        // get app the data sent on bundle
        Bundle bundle= intent.getExtras();
        //lopp through all keys in the bundle
        for (String key : bundle.keySet()) {
        // get object by key( we define object became it may be text or image or whatever
            Object value = bundle.get(key);
        //get all keys
            dataBundel += String.format("%s %s (%s)", key, value.toString(), value.getClass().getName());
        }

        Toast.makeText(context, dataBundel,Toast.LENGTH_LONG).show();

    }
}