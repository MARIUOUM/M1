package com.example.binta.cartesmemoire;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioButton;

public class AjoutCarteActivity extends AppCompatActivity {

    ContentResolver contRes;
    private static String authority = "com.example.binta.flshCrdProvider";
    String theme;
    EditText q;
    EditText r;
    int niveau;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ajout_carte);
        q = (EditText) findViewById(R.id.question);
        r = (EditText) findViewById(R.id.reponse);
        Intent intent = getIntent();
        theme = intent.getStringExtra("theme");
        contRes = this.getContentResolver();
    }

    public void onRadioButtonClicked(View view) {
        boolean checked = ((RadioButton) view).isChecked();

        switch(view.getId()) {
            case R.id.facile:
                if (checked)
                    niveau = 1;
                    break;
            case R.id.moyen:
                if (checked)

                    niveau =2;
                    break;
            case R.id.difficile:
                if (checked)
                    niveau =3;

        }
    }
    public void ajout(View v){
        String th = req(theme);

        if(th==null)
            return;
        String ques = q.getText().toString();
        String rep = r.getText().toString();
        ContentValues cv = new ContentValues();
        cv.put("question", ques);
        cv.put("reponse", rep);
        cv.put("theme", th);
        cv.put("compartiment", "1");
        cv.put("niveau", String.valueOf(niveau));

        Uri.Builder builder = new Uri.Builder();
        builder.scheme("content").authority(authority).appendPath("carte");
        Uri uri = builder.build();
        try {
            contRes.insert(uri, cv);
        } catch (Exception e) {
            Log.d("AjoutCarteActivity", e.getMessage());
        }
        reqQuestion();


    }

    public String req(String t) {
        try {
            Log.d("debu req","ok");
            Uri.Builder builder = new Uri.Builder();
            builder.scheme("content").authority(authority)
                    .appendPath("findTheme")
                    .appendPath(t);
            Uri uri = builder.build();

            Cursor dbCursor = contRes.query(uri, null, null, null, null);

            if(dbCursor.moveToFirst()) {

                String id = dbCursor.getString(dbCursor.getColumnIndex("_id"));
                String tt = dbCursor.getString(dbCursor.getColumnIndex("themetext"));

                Log.d("id: ", id);
                Log.d("theme: ", tt);
                dbCursor.close();
                return id;
            }else{
                return null;
            }

        }catch (Exception e){
            Log.d("req erreur",e.getMessage());
        }
        return null;
    }

    public void reqQuestion() {
        Uri.Builder builder = new Uri.Builder();
        builder.scheme("content").authority(authority)
                .appendPath("carte");
        Uri uri = builder.build();

        Cursor dbCursor = contRes.query(uri, null, null, null, null);
        dbCursor.moveToFirst();
        String id = dbCursor.getString(dbCursor.getColumnIndex("_id"));
        String tt = dbCursor.getString(dbCursor.getColumnIndex("question"));
        String reponse = dbCursor.getString(dbCursor.getColumnIndex("reponse"));
        String theme = dbCursor.getString(dbCursor.getColumnIndex("theme"));
        String c = dbCursor.getString(dbCursor.getColumnIndex("compartiment"));
        String n = dbCursor.getString(dbCursor.getColumnIndex("niveau"));
        dbCursor.close();
        Log.d("id: ", id);
        Log.d("question: ", tt);
        Log.d("reponse: ", reponse);
        Log.d("compartiment: ", c);
        Log.d("theme: ", theme);
        Log.d("niveau: ", n);






    }


}
