package com.example.binta.cartesmemoire;


import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;


public class ListeJeuActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_liste_jeu);

        if (savedInstanceState != null) {
            Log.d("saveinstacestate","not null");
            FragmentManager fm = getSupportFragmentManager();
            getSupportFragmentManager()
                    .popBackStack("debut", FragmentManager.POP_BACK_STACK_INCLUSIVE);
        }
        Log.d("saveinstacestate","fragmentransaction");
        FragmentTransaction transaction = getSupportFragmentManager()
                .beginTransaction();

        ListJeuFragment ljf =  ListJeuFragment.newInstance("","");
        transaction.add(R.id.liste_fragment, ljf);
        transaction.addToBackStack(null).commit();


    }








}
