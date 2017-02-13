package com.example.vijaykumar.final_bizzie;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class InBizzie extends AppCompatActivity {

    TextView user;
    TextView zCode;
    TextView hello;
    TextView yourZip;
    TextView responseView;
    ProgressBar progressBar;
    private static final String TAG = "InBizzie_Activity";
    static final String API_URL = "https://kumar-cs496-a3.appspot.com/get/";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_in_bizzie);

        Intent intent = getIntent();
        Bundle extras = intent.getExtras();
        final String username = extras.getString("UserName");
        final String zip = extras.getString("Zip Code Preference");

        progressBar = (ProgressBar) findViewById(R.id.progressBar);
        responseView = (TextView) findViewById(R.id.responseView);

        user = (TextView) findViewById(R.id.userNameView);
        zCode = (TextView) findViewById(R.id.zipView);

        hello = (TextView) findViewById(R.id.hello);
        yourZip = (TextView) findViewById(R.id.yourZip);

        user.setText(username);
        zCode.setText(zip);

        hello.setText("Hello, ");
        yourZip.setText(". Your Zip Code preference is: ");

        Button changeZip = (Button) findViewById(R.id.changeZip);
        changeZip.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // do something
            }
        });

        Button addBiz = (Button) findViewById(R.id.addBiz);
        addBiz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toBizPage(username, zip);
            }
        });

        Button editBiz = (Button) findViewById(R.id.editBiz);
        editBiz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toEditPage(username, zip);
            }
        });

        Button deleteBiz = (Button) findViewById(R.id.deleteBiz);
        deleteBiz.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toDeletePage(username, zip);
            }
        });

        Button changeZipButton = (Button) findViewById(R.id.changeZip);
        changeZipButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toChangeZip(username, zip);
            }
        });

        Button Logout = (Button) findViewById(R.id.Logout);
        Logout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(InBizzie.this, MainActivity.class);
                startActivity(intent);
            }
        });


        // get businesses

        new RetrieveFeedTask().execute(zip);

    }


    private void toChangeZip(String username, String zip) {

        Intent intent = new Intent(InBizzie.this, ChangeZip.class);
        Bundle extras = new Bundle();
        extras.putString("UserName", username);
        extras.putString("Zip Code Preference", zip);
        intent.putExtras(extras);

        startActivity(intent);
    }

    private void toBizPage(String username, String zip) {

        Intent intent = new Intent(InBizzie.this, NewBiz.class);
        Bundle extras = new Bundle();
        extras.putString("UserName", username);
        extras.putString("Zip Code Preference", zip);
        intent.putExtras(extras);

        startActivity(intent);
    }


    private void toEditPage(String username, String zip) {

        Intent intent = new Intent(InBizzie.this, EditBiz.class);
        Bundle extras = new Bundle();
        extras.putString("UserName", username);
        extras.putString("Zip Code Preference", zip);
        intent.putExtras(extras);

        startActivity(intent);
    }


    private void toDeletePage(String username, String zip) {

        Intent intent = new Intent(InBizzie.this, DeleteBiz.class);
        Bundle extras = new Bundle();
        extras.putString("UserName", username);
        extras.putString("Zip Code Preference", zip);
        intent.putExtras(extras);

        startActivity(intent);
    }

    class RetrieveFeedTask extends AsyncTask<String, Void, String> {

        private Exception exception;

        protected void onPreExecute() {
            progressBar.setVisibility(View.VISIBLE);
            responseView.setText("");
        }

        protected String doInBackground(String... param) {
            Log.v(TAG, "This is the zip code: " + param[0]);

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

                for (int i = 0; i < jArray.length(); i++) {
                    if (i == 0) {
                        printString.append("Zip Code Info:\n\n");
                        printString.append("Zip Code: ").append(jArray.getJSONObject(i).getString("zCode")).append("\n");
                        printString.append("Population: ").append(jArray.getJSONObject(i).getString("population")).append("\n");
                        printString.append("Household Size: ").append(jArray.getJSONObject(i).getString("household_size")).append("\n");
                        printString.append("Income Per Capita: ").append(jArray.getJSONObject(i).getString("income_per_capita")).append("\n\n");
                        printString.append("Business Info: \n");
                    } else {
                        printString.append("Business Name: ").append(jArray.getJSONObject(i).getString("biz_name")).append("\n");
                        printString.append("New Business: ").append(jArray.getJSONObject(i).getString("newBusiness")).append("\n");
                        printString.append("Business Type: ").append(jArray.getJSONObject(i).getString("biz_type")).append("\n");
                        printString.append("Business Description: ").append(jArray.getJSONObject(i).getString("biz_desc")).append("\n");
                        printString.append("Business Customer: ").append(jArray.getJSONObject(i).getString("biz_cust")).append("\n\n");
                    }
                }

            } catch (JSONException e) {
                e.printStackTrace();
            }
            Log.i("INFO", String.valueOf(printString));
            responseView.setText(printString);


        }
    }
}
