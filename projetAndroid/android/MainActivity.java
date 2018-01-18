package com.example.binta.cartesmemoire;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {


    ContentResolver contRes;
    private static String authority = "com.example.binta.flshCrdProvider";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        contRes = this.getContentResolver();
        /*insertTheme("math");
        insertCompartiment("2016", 3);*/

        //req();
        Intent intent = new Intent(this,ListeJeuActivity.class);
        //intent.putExtra("theme","math");
        startActivity(intent);
    }

    public void insertTheme(String nom) {
        ContentValues cv = new ContentValues();
        cv.put("themetext", nom);
        Uri.Builder builder = new Uri.Builder();
        builder.scheme("content").authority(authority).appendPath("theme");
        Uri uri = builder.build();
        try {
            Log.d("Avant INSERSTION", "ok");
            contRes.insert(uri, cv);
            Log.d("APRES INSERSTION", "ok");
        } catch (Exception e) {
            Log.d("MyAcivity", e.getMessage());
        }

    }

    public void insertCompartiment( String date, int interval) {
        ContentValues cv = new ContentValues();
        cv.put("date", date);
        cv.put("intervalle", String.valueOf(interval));
        Uri.Builder builder = new Uri.Builder();
        builder.scheme("content").authority(authority).appendPath("compartiment");
        Uri uri = builder.build();
        try {
            Log.d("Avant INSERSTIONComp", "ok");
            contRes.insert(uri, cv);
            Log.d("APRES INSERSTIONComp", "ok");
        } catch (Exception e) {
            Log.d("MyAcivity", e.getMessage());
        }


    }

    public void req() {
        Uri.Builder builder = new Uri.Builder();
        builder.scheme("content").authority(authority)
                .appendPath("findTheme");
        Uri uri = builder.build();

            Cursor dbCursor = contRes.query(uri, null, null, null, null);
            dbCursor.moveToFirst();
            String id = dbCursor.getString(dbCursor.getColumnIndex("id"));
            String tt = dbCursor.getString(dbCursor.getColumnIndex("themetext"));
            dbCursor.close();
            Log.d("___________id: ", id);
            Log.d("_____________theme: ", tt);


            builder = new Uri.Builder();
            builder.scheme("content").authority(authority)
                    .appendPath("findComp");
            uri = builder.build();
            try {
                dbCursor = contRes.query(uri, null, null, null, null);
                dbCursor.moveToFirst();
                id = dbCursor.getString(dbCursor.getColumnIndex("id"));
                tt = dbCursor.getString(dbCursor.getColumnIndex("date"));
                String ttt = dbCursor.getString(dbCursor.getColumnIndex("intervalle"));
                dbCursor.close();
                Log.d("id: ", id);
                Log.d("date: ", tt);
                Log.d("interval", ttt);


            } catch (Exception e) {
                Log.d("Erreur: ", e.getMessage());
            }

    }
}
