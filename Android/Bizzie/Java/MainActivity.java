package com.example.vijaykumar.final_bizzie;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;


public class MainActivity extends AppCompatActivity {


    TextView responseView;
    EditText user;
    EditText pass;
    ProgressBar progressBar;
    static final String API_URL = "https://kumar-cs496-a3.appspot.com/user/";
    private static final String TAG = "Main_Activity";
    public final static String EXTRA_MESSAGE = "com.example.vijaykumar.final_bizzie.MESSAGE";
    private static final int MY_PERMISSIONS_REQUEST_ACCESS_FINE_LOCATION = 1;

    // TextWatcher Code borrowed from:
    // http://stackoverflow.com/questions/15002963/in-android-how-to-make-login-button-disable-with-respect-to-edittext
    // create a textWatcher member
    private TextWatcher mTextWatcher = new TextWatcher() {
        @Override
        public void beforeTextChanged(CharSequence charSequence, int i, int i2, int i3) {
        }

        @Override
        public void onTextChanged(CharSequence charSequence, int i, int i2, int i3) {
        }

        @Override
        public void afterTextChanged(Editable editable) {
            // check Fields For Empty Values
            checkFieldsForEmptyValues();
        }
    };

    void checkFieldsForEmptyValues(){
        Button b = (Button) findViewById(R.id.LoginButton);

        String s1 = user.getText().toString();
        String s2 = pass.getText().toString();

        if(s1.equals("")|| s2.equals("")){
            b.setEnabled(false);
        } else {
            b.setEnabled(true);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /////////////////////// PERMISSIONS /////////////////////////////

        int permissionCheck = ContextCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_FINE_LOCATION);

        if (permissionCheck == -1) {

            ActivityCompat.requestPermissions(this,
                    new String[]{android.Manifest.permission.ACCESS_FINE_LOCATION},
                    MY_PERMISSIONS_REQUEST_ACCESS_FINE_LOCATION);
        }

        user = (EditText) findViewById(R.id.username);
        pass = (EditText) findViewById(R.id.password);


        // set listeners
        user.addTextChangedListener(mTextWatcher);
        pass.addTextChangedListener(mTextWatcher);

        // run once to disable if empty
        checkFieldsForEmptyValues();

        responseView = (TextView) findViewById(R.id.responseView);
        user = (EditText) findViewById(R.id.username);
        pass = (EditText) findViewById(R.id.password);
        progressBar = (ProgressBar) findViewById(R.id.progressBar);


        Button LoginButton = (Button) findViewById(R.id.LoginButton);
        LoginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new attemptLogin().execute(user.getText().toString() + "/" + pass.getText().toString());
            }
        });

        Button newUserButton = (Button) findViewById(R.id.newuser);
        newUserButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                createNewUser();
            }
        });

    }

    private void createNewUser() {

        Intent intent = new Intent(MainActivity.this, NewUser.class);
        startActivity(intent);
    }


    class attemptLogin extends AsyncTask<String, Void, String>
    {
        protected void onPreExecute() {
            progressBar.setVisibility(View.VISIBLE);
            responseView.setText("");
        }


        protected String doInBackground(String... param) {
            Log.v(TAG, "The user/pass is: " + param[0]);

            try {
                URL url = new URL(API_URL + param[0]);
                HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
                try {
                    BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(urlConnection.getInputStream()));
                    StringBuilder stringBuilder = new StringBuilder();
                    String line;
                    while ((line = bufferedReader.readLine()) != null) {
                        stringBuilder.append(line).append("\n");
                    }
                    bufferedReader.close();
                    return stringBuilder.toString();
                } finally {
                    urlConnection.disconnect();
                }
            } catch (Exception e) {
                Log.e("ERROR", e.getMessage(), e);
                return null;
            }
        }


        protected void onPostExecute(String response) {
            if (response == null) {
                response = "THERE WAS AN ERROR";
            }
            progressBar.setVisibility(View.GONE);
            StringBuilder printString = new StringBuilder();
            try {

                JSONArray jArray = new JSONArray(response);
                //String message = jArray.getJSONObject(0).getString("message");


                if(jArray.getJSONObject(0).has("message"))
                    printString.append(jArray.getJSONObject(0).getString("message"));

                else
                {

                    String user = jArray.getJSONObject(0).getString("user_name");
                    String zPref = jArray.getJSONObject(0).getString("zip_pref");

                    Intent intent = new Intent(MainActivity.this, InBizzie.class);
                    Bundle extras = new Bundle();
                    extras.putString("UserName", user);
                    extras.putString("Zip Code Preference", zPref);
                    intent.putExtras(extras);
                    startActivity(intent);

                }



            } catch (JSONException e) {
                e.printStackTrace();
            }
            Log.i("INFO", String.valueOf(printString));
            responseView.setText(printString);


        }



    }




}
