package com.example.binta.cartesmemoire;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class AcceuilActivity extends AppCompatActivity {

    ListView listView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_acceuil);

        listView = (ListView) findViewById(R.id.lv);

        String[] choix = { "Ajouter jeu de carte", "Afficher carte" };

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.activity_list_item, android.R.id.text1, choix);

        // on assigne l'adapter à notre list
        listView.setAdapter(adapter);
    }
}
