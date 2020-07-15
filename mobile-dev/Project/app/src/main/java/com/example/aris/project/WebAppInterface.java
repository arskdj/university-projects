package com.example.aris.project;

import android.content.Context;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.webkit.JavascriptInterface;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import com.parse.FindCallback;
import com.parse.GetCallback;
import com.parse.Parse;
import com.parse.ParseException;
import com.parse.ParseObject;
import com.parse.ParseQuery;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by aris on 1/17/16.
 */
public class WebAppInterface {
    static final String MSG_ERROR = "Something went wrong. Are you connected to the internet?";

    Context mContext;
    static ParseObject gameScore;
    MediaPlayer mediaPlayer;
    static String user_id;
    static String user_rank;
    static ArrayList<String> top10;

    /** Instantiate the interface and set the context */
    WebAppInterface(Context c) {
        mContext = c;
        mediaPlayer = MediaPlayer.create(mContext, R.raw.ding);
        top10 = new ArrayList<>();
        initDB();
    }


    private void createNewObject(){
        gameScore = new ParseObject("ding");
        gameScore.put("count", 0);
    }

    private void savePrefsUserId(){
        //save user_id
        SharedPreferences.Editor editor = mContext.getSharedPreferences("prefs",0).edit();
        editor.putString("user_id", user_id);
        editor.commit();
    }

    public void initDB(){
        //init parse
        Parse.enableLocalDatastore(mContext);
        Parse.initialize(mContext);
        //load user_id
        SharedPreferences sp = mContext.getSharedPreferences("prefs", 0);
        user_id = sp.getString("user_id", "notset");

        if (user_id.equals("notset") ){
            //create new user_id
            createNewObject();
            try {
                gameScore.save();
                gameScore.pin();
            } catch (ParseException e) {
                e.printStackTrace();
            }
            user_id = gameScore.getObjectId();
            //save userid in shared preferences
            if (user_id!=null)
            savePrefsUserId();
        }else{
            ParseQuery<ParseObject> query = ParseQuery.getQuery("ding");
            query.fromLocalDatastore();
            query.getInBackground(user_id, new GetCallback<ParseObject>() {
                @Override
                public void done(ParseObject object, com.parse.ParseException e) {
                    if (e == null) {
                        // object will be your game score
                        showToast("Welcome " + user_id);
                        gameScore = object;
                    } else {
                        // something went wrong
                        createNewObject();
                    }
                }
            });
        }
    }

    @JavascriptInterface
    public void ding() {
        if (!mediaPlayer.isPlaying()) {
            mediaPlayer.start();
            gameScore.increment("count", 1);
            gameScore.saveEventually();
        }
    }
    /** Show a toast from the web page */
    @JavascriptInterface
    public void showToast( String toast) {
        Toast.makeText(mContext, toast, Toast.LENGTH_SHORT).show();
    }

    public static void showToast2(Context context, String toast) {
        Toast.makeText(context, toast, Toast.LENGTH_SHORT).show();
    }

    private static String calculateTime(int score) {
        int totalSeconds = score*7;//to ding pai 7 defterolepta
        int hours = totalSeconds/60/60;
        totalSeconds -= hours*60*60;
        int minutes = totalSeconds/60;
        totalSeconds -= minutes*60;
        return hours+"h "+minutes+"m "+totalSeconds+"s";
    }

    //Statistics Activity methods

    public static void getTotalShames(final Context context, final boolean localDB){
        final ParseQuery<ParseObject> query = ParseQuery.getQuery("ding");
        query.whereGreaterThan("count", 0);
        query.addDescendingOrder("count");
        if (localDB) {
            query.fromLocalDatastore();
        }
        query.findInBackground(new FindCallback<ParseObject>() {
            public void done(List<ParseObject> scoreList, com.parse.ParseException e) {
                if (e == null) {
                    String obj_id="";
                    showToast2(context, "Retrieved " + scoreList.size() + " scores");
                    Integer total = 0;
                    int counter = 0;
                    for (ParseObject obj : scoreList) {
                        //save other user objects in local db
                        //if we are querying from the remote db
                        if (!localDB)
                            obj.pinInBackground();
                        //get user rank
                        if (obj.getObjectId().equals(user_id)) {
                            user_rank = String.valueOf(counter+1);
                        }
                        //save top10 to arraylist
                        if (counter < 10) {
                            obj_id = obj.getObjectId();
                            if (obj_id.equals(user_id)){
                                obj_id="***YOU***";
                            }
                            top10.add(counter + 1 + ". " + obj_id + ": " + obj.getInt("count"));
                        }
                        total += obj.getInt("count");
                        counter++;
                    }
                    showToast2(context, "total shames: " + total);
                    //save to txts
                    String alltime = calculateTime(total);
                    StatisticsActivity.txtAllScore.setText(String.valueOf(total));
                    StatisticsActivity.txtAllTime.setText(alltime);
                    StatisticsActivity.txtUserRank.setText(user_rank);
                    //set top10 listview
                    String [] top10strings = top10.toArray(new String[top10.size()]);
                    top10.clear();
                    StatisticsActivity.listView.setAdapter(new ArrayAdapter<String>(context, android.R.layout.simple_list_item_1,top10strings));
                } else {
                    showToast2(context, e.getMessage());
                }
            }
        });
    }


    public static void getUserScore(final Context context,boolean localDB){
        //get user id from prefs
        SharedPreferences sp = context.getSharedPreferences("prefs", 0);
        final String user_id = sp.getString("user_id", "notset");

        //get object from db
        ParseQuery<ParseObject> query = ParseQuery.getQuery("ding");
        if (localDB)
            query.fromLocalDatastore();
        query.getInBackground(user_id, new GetCallback<ParseObject>() {
            @Override
            public void done(ParseObject object, com.parse.ParseException e) {
                int userScore = 0;
                //success
                if (e == null) {
                    // object will be your game score
                    showToast2(context, "loaded user_id: " + user_id);
                    userScore = object.getInt("count");
                    //save to txts
                    String usertime = calculateTime(userScore);
                    StatisticsActivity.txtUserId.setText(user_id);
                    StatisticsActivity.txtUserScore.setText(String.valueOf(userScore));
                    StatisticsActivity.txtUserTime.setText(usertime);
                } else {
                    //error
                    showToast2(context, e.getMessage());
                    showToast2(context,"You need to connect to the internet for the first time.");
                }
            }
        });
    }

    //refresh
    public static void refreshFromRemoteDB(Context context){
        getUserScore(context,false);
        getTotalShames(context, false);
    }
}