package com.example.vijaykumar.final_bizzie;

import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
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

public class NewBiz extends AppCompatActivity {

    TextView user;
    TextView zCode;
    TextView responseView;
    EditText bizName;
    EditText newBiz;
    EditText bizType;
    EditText bizDesc;
    EditText bizCust;
    EditText zipC;

    ProgressBar progressBar;

    static final String POST_URL = "https://kumar-cs496-a3.appspot.com/post/";
    private static final String TAG = "NewBiz_Activity";



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
        Button b = (Button) findViewById(R.id.submitButton);
        

        String s1 = bizName.getText().toString();
        String s2 = newBiz.getText().toString();
        String s3 = bizType.getText().toString();
        String s4 = bizDesc.getText().toString();
        String s5 = bizCust.getText().toString();
        String s6 = zipC.getText().toString();

        if(s1.equals("")|| s2.equals("") || s3.equals("")|| s4.equals("") || s5.equals("")|| s6.equals("")){
            b.setEnabled(false);
        } else {
            b.setEnabled(true);
        }
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_new_biz);


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
        newBiz = (EditText) findViewById(R.id.newBusiness);
        bizType = (EditText) findViewById(R.id.biz_type);
        bizDesc = (EditText) findViewById(R.id.biz_desc);
        bizCust = (EditText) findViewById(R.id.biz_cust);
        zipC = (EditText) findViewById(R.id.zCode);

        progressBar = (ProgressBar) findViewById(R.id.progressBar);
        responseView = (TextView) findViewById(R.id.responseView);


        // set listeners
        bizName.addTextChangedListener(mTextWatcher);
        newBiz.addTextChangedListener(mTextWatcher);
        bizType.addTextChangedListener(mTextWatcher);
        bizDesc.addTextChangedListener(mTextWatcher);
        bizCust.addTextChangedListener(mTextWatcher);
        zipC.addTextChangedListener(mTextWatcher);


        // run once to disable if empty
        checkFieldsForEmptyValues();




        Button SubmitButton = (Button) findViewById(R.id.submitButton);
        SubmitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new submitPost().execute(bizName.getText().toString()+
                        "/"+ newBiz.getText().toString() +
                        "/"+bizType.getText().toString() +
                        "/"+bizDesc.getText().toString() +
                        "/"+bizCust.getText().toString() +
                        "/"+zCode.getText().toString());
            }
        });

        Button HomeButton = (Button) findViewById(R.id.Home);
        HomeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(NewBiz.this, InBizzie.class);
                Bundle extras = new Bundle();
                extras.putString("UserName", username);
                extras.putString("Zip Code Preference", zip);
                intent.putExtras(extras);

                startActivity(intent);
            }
        });

    }



    class submitPost extends AsyncTask<String, Void, String> {
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
                connection.setRequestMethod("POST");
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

                postString.append("New Business Added!\n\n")
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
