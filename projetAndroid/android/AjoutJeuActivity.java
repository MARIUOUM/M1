package com.example.binta.cartesmemoire;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

public class AjoutJeuActivity extends AppCompatActivity {

    EditText theme;
    ContentResolver contRes;
    private static String authority = "com.example.binta.flshCrdProvider";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ajout_jeu);
        theme = (EditText) findViewById(R.id.jeu);
        contRes = this.getContentResolver();
    }

    public void valider(View view){
        String jeu = String.valueOf(theme.getText());
        ContentValues cv = new ContentValues();
        cv.put("themetext", jeu);
        Uri.Builder builder = new Uri.Builder();
        builder.scheme("content").authority(authority).appendPath("theme");
        Uri uri = builder.build();
        try {
            contRes.insert(uri, cv);
        } catch (Exception e){
            Log.d("AjoutJeuActivity", e.getMessage());
        }

    }
}
