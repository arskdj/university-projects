package com.example.aris.project;

import android.app.ListActivity;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.parse.FindCallback;
import com.parse.GetCallback;
import com.parse.ParseObject;
import com.parse.ParseQuery;

import java.util.List;

public class StatisticsActivity extends AppCompatActivity {

    static TextView txtUserScore;
    static TextView txtUserTime;
    static TextView txtAllScore;
    static TextView txtAllTime;
    static TextView txtUserId;
    static TextView txtUserRank;
    static ListView listView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_statistics);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                WebAppInterface.refreshFromRemoteDB(StatisticsActivity.this);
                Snackbar.make(view, "Getting Data from Remote DB", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        // get items
        txtUserScore = (TextView) findViewById(R.id.txtUserScore);
        txtUserTime = (TextView) findViewById(R.id.txtUserTime);
        txtAllScore = (TextView) findViewById(R.id.txtAllScore);
        txtAllTime = (TextView) findViewById(R.id.txtAllTime);
        txtUserId = (TextView) findViewById(R.id.txtUserId);
        txtUserRank = (TextView) findViewById(R.id.txtUserRank);
        listView = (ListView) findViewById(R.id.listView);

        // set items
        WebAppInterface.getUserScore(this, true);
        WebAppInterface.getTotalShames(this, true);
    }
}
