package com.example.binta.cartesmemoire;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

/**
 * Created by binta on 16/12/16.
 */
public class BaseFlashCard extends SQLiteOpenHelper {

    public final static int VERSION = 2;
    public final static String DB_NAME = "base_flash_card";
    public final static String TABLE_CARTE = "carte";
    public final static String COLONNE_ID = "_id";
    public final static String COLONNE_QUESTION = "question";
    public final static String COLONNE_REPONSE = "reponse";
    public final static String COLONNE_THEME = "theme";
    public  final static String COLONNE_NIVEAU="niveau";


    public final static String TABLE_THEME = "theme";
    public final static String COLONNE_THEMETEXT = "themetext";

    public final static String TABLE_COMPARTIMENT = "compartiment";
    public final static String COLONNE_INTERVALLE = "intervalle";
    public final static String COLONNE_date = "date";


    public final static String CREATE_THEME = "create table " + TABLE_THEME + " (" +
            COLONNE_ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
            COLONNE_THEMETEXT + " string NOT NULL unique " + ");";

    public final static String CREATE_COMPARTIMENT = "create table " + TABLE_COMPARTIMENT + "(" +

            COLONNE_ID+" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "+
            COLONNE_date + " string NOT NULL, "+
            COLONNE_INTERVALLE+ " integer NOT NULL );";

    public final static String CREATE_CARTE = "create table " + TABLE_CARTE + "(" +
            COLONNE_ID + " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " +
            COLONNE_QUESTION + " string NOT NULL, " +
            COLONNE_REPONSE +" string NOT NULL,"+
            TABLE_COMPARTIMENT + " INTEGER NOT NULL, " +
            COLONNE_THEME + " INTEGER NOT NULL, " +
            COLONNE_NIVEAU+" INTEGER NOT NULL ,"+
            " FOREIGN KEY ("+TABLE_COMPARTIMENT+") REFERENCES "+TABLE_COMPARTIMENT+" ("+COLONNE_ID+"), "+
            " FOREIGN KEY ("+COLONNE_THEME+") REFERENCES "+TABLE_THEME+" ("+COLONNE_ID+") " + ");";



    public BaseFlashCard(Context context) {
        super(context, DB_NAME, null, VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_THEME);
        db.execSQL(CREATE_COMPARTIMENT);
        db.execSQL(CREATE_CARTE);

    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        if (newVersion > oldVersion) {

            db.execSQL("drop table if exists " + TABLE_CARTE);
            db.execSQL("drop table if exists " + TABLE_COMPARTIMENT);
            db.execSQL("drop table if exists " + TABLE_THEME);
            onCreate(db);
        }
    }
}