package com.example.vijaykumar.final_bizzie;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

public class EditBiz extends AppCompatActivity {


    TextView user;
    TextView zCode;
    TextView responseView;
    EditText ubizName;
    EditText unewBiz;
    EditText ubizType;
    EditText ubizDesc;
    EditText ubizCust;
    EditText bizName;
    EditText zipC;

    ProgressBar progressBar;

    static final String POST_URL = "https://kumar-cs496-a3.appspot.com/put/";
    private static final String TAG = "EditBiz_Activity";


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
        Button b = (Button) findViewById(R.id.submitButton);

        String s1 = bizName.getText().toString();
        String s2 = zipC.getText().toString();
        String s3 = ubizName.getText().toString();
        String s4 = ubizType.getText().toString();
        String s5 = unewBiz.getText().toString();
        String s6 = ubizCust.getText().toString();
        String s7 = ubizDesc.getText().toString();


        if(s1.equals("")|| s2.equals("") || s3.equals("")|| s4.equals("") || s5.equals("")|| s6.equals("") || s7.equals("")  ){
            b.setEnabled(false);
        } else {
            b.setEnabled(true);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_biz);


        Intent intent = getIntent();
        Bundle extras = intent.getExtras();
        final String username = extras.getString("UserName");
        final String zip = extras.getString("Zip Code Preference");


        user = (TextView) findViewById(R.id.userNameView);
        zCode = (TextView) findViewById(R.id.zipView);

        user.setText(username);
        zCode.setText(zip);

        responseView = (TextView) findViewById(R.id.responseView);

        bizName = (EditText) findViewById(R.id.biz_name);
        zipC = (EditText) findViewById(R.id.zCode);

        ubizName = (EditText) findViewById(R.id.u_biz_name);
        unewBiz = (EditText) findViewById(R.id.newBusiness);
        ubizType = (EditText) findViewById(R.id.biz_type);
        ubizDesc = (EditText) findViewById(R.id.biz_desc);
        ubizCust = (EditText) findViewById(R.id.biz_cust);

        // set listeners
        bizName.addTextChangedListener(mTextWatcher);
        zipC.addTextChangedListener(mTextWatcher);
        ubizName.addTextChangedListener(mTextWatcher);
        ubizType.addTextChangedListener(mTextWatcher);
        unewBiz.addTextChangedListener(mTextWatcher);
        ubizDesc.addTextChangedListener(mTextWatcher);
        ubizCust.addTextChangedListener(mTextWatcher);


        // run once to disable if empty
        checkFieldsForEmptyValues();



        progressBar = (ProgressBar) findViewById(R.id.progressBar);
        responseView = (TextView) findViewById(R.id.responseView);


        Button SubmitButton = (Button) findViewById(R.id.submitButton);
        SubmitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new submitPut().execute(bizName.getText().toString()+
                        "/"+ zCode.getText().toString() +
                        "/"+ ubizName.getText().toString() +
                        "/"+ unewBiz.getText().toString() +
                        "/"+ ubizType.getText().toString() +
                        "/"+ ubizDesc.getText().toString() +
                        "/"+ ubizCust.getText().toString());
            }
        });


        Button HomeButton = (Button) findViewById(R.id.Home);
        HomeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(EditBiz.this, InBizzie.class);
                Bundle extras = new Bundle();
                extras.putString("UserName", username);
                extras.putString("Zip Code Preference", zip);
                intent.putExtras(extras);

                startActivity(intent);
            }
        });
    }



    class submitPut extends AsyncTask<String, Void, String> {
        private Exception exception;

        protected void onPreExecute() {
            progressBar.setVisibility(View.VISIBLE);
            responseView.setText("");
        }

        protected String doInBackground(String... param) {


            try {

                URL url = new URL(POST_URL + param[0]);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                Log.v(TAG, String.valueOf(connection));
                connection.setRequestMethod("PUT");
                connection.setRequestProperty("ACCEPT-LANGUAGE", "en-US,en;0.5");
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

                JSONObject jObj = new JSONObject(response);

                postString.append("Business has been edited!\n\n")
                        .append("Business Name: " + jObj.getString("biz_name") + "\n")
                        .append("New Business: " + jObj.getString("newBusiness") + "\n")
                        .append("Business Type: " + jObj.getString("biz_type") + "\n")
                        .append("Business Description: " + jObj.getString("biz_desc") + "\n")
                        .append("Business Customer: " + jObj.getString("biz_cust"));


            } catch (JSONException e) {
                e.printStackTrace();
            }


            Log.i("INFO", String.valueOf(postString));
            responseView.setText(postString);


        }


    }
}

