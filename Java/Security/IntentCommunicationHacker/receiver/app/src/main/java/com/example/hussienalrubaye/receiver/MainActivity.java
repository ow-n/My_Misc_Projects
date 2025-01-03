package com.example.hussienalrubaye.receiver;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Define the display Text view
        TextView txtview=(TextView)findViewById(R.id.txtDisplay);
        // get app the data sent on bundle
        Bundle b = getIntent().getExtras();


        // display the key that have the data
        txtview.setText(b.getString("Comment"));

        // Check if bundle exists and contains the "Comment" key
        if (b != null && b.containsKey("Comment")) {
            // dipher code
            String dencryptedMessage = decipher(b.getString("Comment"), 42);
            txtview.setText(dencryptedMessage);
        } else {
            txtview.setText("No comment received");
        }
    }

    // dipher encryption add shift for key
    String decipher(String msg, int shift){
        String s = "";
        int len = msg.length(); // get string length
        for(int x = 0; x < len; x++){
            char c = (char)(msg.charAt(x) - shift);  // shift every character
            s += c; // append the characters
        }
        return s;
    }
}

