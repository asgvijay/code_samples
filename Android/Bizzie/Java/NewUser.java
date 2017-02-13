package com.example.vijaykumar.final_bizzie;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

public class NewUser extends AppCompatActivity {

    EditText user;
    EditText pass;
    EditText zip;
    ProgressBar progressBar;
    TextView responseView;
    private static final String TAG = "New_User";



    static final String API_URL = "https://kumar-cs496-a3.appspot.com/createuser/";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_new_user);


        responseView = (TextView) findViewById(R.id.responseView);
        user = (EditText) findViewById(R.id.username);
        pass = (EditText) findViewById(R.id.password);
        zip = (EditText) findViewById(R.id.zip_code);
        progressBar = (ProgressBar) findViewById(R.id.progressBar);


        Button CreateButton = (Button) findViewById(R.id.CreateUser);
        CreateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new createUser().execute(user.getText().toString() + "/" + pass.getText().toString() + "/" + zip.getText().toString());
            }
        });


        Button Login = (Button) findViewById(R.id.Login);
        Login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(NewUser.this, MainActivity.class);
                startActivity(intent);


            }
        });

    }



    class createUser extends AsyncTask<String, Void, String>
    {
        private Exception exception;

        protected void onPreExecute() {
            progressBar.setVisibility(View.VISIBLE);
            responseView.setText("");
        }

        protected String doInBackground(String... param) {


            try {
                URL url = new URL(API_URL + param[0]);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                Log.v(TAG, String.valueOf(connection));
                connection.setRequestMethod("POST");
                //connection.setRequestProperty("ACCEPT-LANGUAGE", "en-US,en;0.5");
                //connection.setRequestProperty("Content-Type", "application/json; charset=UTF-8");
                connection.setDoOutput(true);
                BufferedWriter buffWrite =
                        new BufferedWriter(new OutputStreamWriter(connection.getOutputStream()));
                Log.v(TAG, "This is the string sent in: " + param[0]);
                //buffWrite.write(param[0]);
                buffWrite.close();

                int responseCode = connection.getResponseCode();
                String responseMessage = connection.getResponseMessage();
                Log.v(TAG, "this is responseCode: " + responseCode);
                Log.v(TAG, "this is responseMessage: " + responseMessage);

                if (responseCode != 500) {
                    try {

                        BufferedReader reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                        String line = "";
                        StringBuilder responseOutput = new StringBuilder();
                        while ((line = reader.readLine()) != null) {
                            responseOutput.append(line);
                        }
                        reader.close();

                        return responseOutput.toString();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }

            } catch (Exception e) {
                e.printStackTrace();
            }

            return null;
        }


        protected void onPostExecute(String response) {
            if (response == null) {
                response = "THERE WAS AN ERROR";
            }
            progressBar.setVisibility(View.GONE);
            StringBuilder printString = new StringBuilder();

            Log.v(TAG, "in POSTEXECUTE: " + response);
            StringBuilder postString = new StringBuilder();
            try {

                //JSONObject jObj = new JSONObject(response);
                JSONArray jArray = new JSONArray(response);

                //postString.append(jObj.getString("message") + "\n");
                postString.append(jArray.getJSONObject(0).getString("message"));

            } catch (JSONException e) {
                e.printStackTrace();
            }


            Log.i("INFO", String.valueOf(postString));
            responseView.setText(postString);


        }



    }
}
