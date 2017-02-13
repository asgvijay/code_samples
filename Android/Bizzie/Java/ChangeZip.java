package com.example.vijaykumar.final_bizzie;

import android.content.Intent;
import android.icu.text.DateFormat;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesNotAvailableException;
import com.google.android.gms.common.GooglePlayServicesRepairableException;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.location.places.Places;
import com.google.android.gms.location.places.ui.PlacePicker;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Date;
import java.util.List;
import java.util.Locale;

public class ChangeZip extends AppCompatActivity implements GoogleApiClient.ConnectionCallbacks,
        GoogleApiClient.OnConnectionFailedListener, LocationListener {


    ProgressBar progressBar;

    private static final String TAG = "ChangeZip_Activity";
    static final String EDIT_ZIP = "https://kumar-cs496-a3.appspot.com/edituserzip/";

    private static final int PLACE_PICKER_REQUEST = 1;

    TextView user;
    TextView zCode;
    TextView hello;
    TextView yourZip;
    TextView responseView;
    EditText zipC;

    boolean usingLocation = false;

    boolean mRequestingLocationUpdates = true;
    Location userLoc;

    String user_zip = null;
    double latitude = 0;
    double longitude = 0;
    Geocoder geocoder;
    List<Address> address = null;
    android.location.Address userAddress = null;

    private GoogleApiClient mGoogleApiClient;
    private LocationRequest mLocationRequest;
    LocationManager mLocationManager;

    private LocationListener locListener;

    PlacePicker.IntentBuilder builder;

    String zip;


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
        Button b = (Button) findViewById(R.id.ChangeZip);

        String s1 = zipC.getText().toString();


        if(s1.equals("")){
            b.setEnabled(false);
        } else {
            b.setEnabled(true);
        }
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_change_zip);


        Intent intent = getIntent();
        Bundle extras = intent.getExtras();
        final String username = extras.getString("UserName");
        zip = extras.getString("Zip Code Preference");


        user = (TextView) findViewById(R.id.userNameView);
        zCode = (TextView) findViewById(R.id.zipView);

        hello = (TextView) findViewById(R.id.hello);
        yourZip = (TextView) findViewById(R.id.yourZip);


        progressBar = (ProgressBar) findViewById(R.id.progressBar);
        responseView = (TextView) findViewById(R.id.responseView);

        user.setText(username);
        zCode.setText(zip);

        hello.setText("Hello, ");
        yourZip.setText(". Your Zip Code preference is: ");

        zipC = (EditText) findViewById(R.id.zCode);


        // set listeners
        zipC.addTextChangedListener(mTextWatcher);


        // run once to disable if empty
        checkFieldsForEmptyValues();


        mGoogleApiClient = new GoogleApiClient
                .Builder(this)
                .enableAutoManage(this, this)
                .addApi(Places.GEO_DATA_API)
                .addApi(Places.PLACE_DETECTION_API)
                .addApi(LocationServices.API)
                .addConnectionCallbacks(this)
                .build();

        mLocationManager = (LocationManager) this.getSystemService(LOCATION_SERVICE);


        Button changeZipButton = (Button) findViewById(R.id.ChangeZip);
        changeZipButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new editZip().execute(username + "/" + zipC.getText().toString());

            }
        });


        Button useLocation = (Button) findViewById(R.id.useLocation);
        useLocation.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                usingLocation = true;
                new editZip().execute(username + "/" + user_zip);

            }
        });


        Button HomeButton = (Button) findViewById(R.id.Home);
        HomeButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChangeZip.this, InBizzie.class);
                Bundle extras = new Bundle();
                extras.putString("UserName", username);
                extras.putString("Zip Code Preference", zip);
                intent.putExtras(extras);

                startActivity(intent);
            }
        });


        Button RefreshButton = (Button) findViewById(R.id.Refresh);
        RefreshButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ChangeZip.this, ChangeZip.class);
                Bundle extras = new Bundle();
                extras.putString("UserName", username);
                extras.putString("Zip Code Preference", zip);
                intent.putExtras(extras);

                startActivity(intent);
            }
        });
    }


    class editZip extends AsyncTask<String, Void, String> {
        private Exception exception;

        protected void onPreExecute() {
            progressBar.setVisibility(View.VISIBLE);
            responseView.setText("");
        }

        protected String doInBackground(String... param) {


            try {

                URL url = new URL(EDIT_ZIP + param[0]);
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                Log.v(TAG, String.valueOf(connection));
                connection.setRequestMethod("PUT");
                connection.setRequestProperty("ACCEPT-LANGUAGE", "en-US,en;0.5");
                connection.setRequestProperty("Content-Type", "application/json; charset=UTF-8");
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
            if(usingLocation)
                zip = user_zip;
            else
                zip = zipC.getText().toString();

            progressBar.setVisibility(View.GONE);

            Log.v(TAG, "in POSTEXECUTE: " + response);
            StringBuilder postString = new StringBuilder();
            try {

                JSONObject jObj = new JSONObject(response);

                postString.append(jObj.getString("message") + "\n");


            } catch (JSONException e) {
                e.printStackTrace();
            }


            Log.i("INFO", String.valueOf(postString));
            responseView.setText(postString);


        }


    }

    @Override
    protected void onStart() {
        Log.v(TAG, "In onStart.");
        super.onStart();
        //mGoogleApiClient.connect();
    }


    @Override
    protected void onResume() {
        Log.v(TAG, "In onResume.");
        super.onResume();
        mGoogleApiClient.connect();


        if (mGoogleApiClient.isConnected())
            Log.v(TAG, "We're connected in onResume");


    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mGoogleApiClient.isConnected()) {
            LocationServices.FusedLocationApi.removeLocationUpdates(mGoogleApiClient, this);
            mGoogleApiClient.disconnect();
        }
    }


    @Override
    protected void onStop() {
        Log.v(TAG, "In onStop.");
        super.onStop();
        mGoogleApiClient.disconnect();
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {

        if (mGoogleApiClient.isConnected())
            Log.v(TAG, "In onConnected and CONNECTED!.");

        userLoc = LocationServices.FusedLocationApi.getLastLocation(mGoogleApiClient);

        if (userLoc != null) {
            latitude = userLoc.getLatitude();
            Log.v(TAG, "The USER Lat IS: " + latitude);
            longitude = userLoc.getLongitude();
            Log.v(TAG, "The USER Long IS: " + longitude);
            geocoder = new Geocoder(this, Locale.getDefault());
            Log.v(TAG, "The USER geocode IS: " + geocoder);
            try {
                address = geocoder.getFromLocation(latitude, longitude, 1);
                Log.v(TAG, "The USER address IS: " + address);
            } catch (IOException e) {
                e.printStackTrace();
            }


            if (address.size() > 0)
                userAddress = address.get(0);

            if (userAddress != null) {
                user_zip = userAddress.getPostalCode();
                Log.v(TAG, "The USER ZIP IS: " + user_zip);
            }
        }

        else{
            if (mRequestingLocationUpdates)
            startLocationUpdates();
        }

        Log.v(TAG, String.valueOf(userLoc));

    }

    @Override
    public void onConnectionSuspended(int i) {

        Log.v(TAG, "In onConnectionSuspended.");

    }

    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {
        Log.v(TAG, "In onConnectionFailed.");
    }


    @Override
    public void onLocationChanged(Location location) {

        Log.v(TAG, "In onLocationChanged.");
        userLoc = location;
        //mLastUpdateTime = DateFormat.getTimeInstance().format(new Date());
        Log.v(TAG, String.valueOf(userLoc));
        handleNewLocation(location);

    }

    protected void startLocationUpdates() {

        Log.v(TAG, "in startLocatinUpdates");


        mLocationRequest = LocationRequest.create()
                .setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY)
                .setInterval(1 * 1000)        // 5 seconds, in milliseconds
                .setFastestInterval(1 * 1000); // 1 second, in milliseconds

        LocationServices.FusedLocationApi.requestLocationUpdates(mGoogleApiClient, mLocationRequest, this);



    }


    private void handleNewLocation(Location location) {
        Log.d(TAG, location.toString());

        latitude = location.getLatitude();
        longitude = location.getLongitude();
        geocoder = new Geocoder(getApplicationContext(), Locale.getDefault());

        try {
            address = geocoder.getFromLocation(latitude, longitude, 1);
        } catch (IOException e) {
            e.printStackTrace();
        }


        if (address.size() > 0)
            userAddress = address.get(0);

        if (userAddress != null) {
            user_zip = userAddress.getPostalCode();
            Log.v(TAG, "The USER ZIP IS: " + user_zip);
        }

            }

        };






