package com.example.binta.cartesmemoire;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;
import android.util.Log;

import java.util.List;

public class FCContentProvider extends ContentProvider {

    private static String authority = "com.example.binta.flshCrdProvider";
    private static  final int THEME = 1;
    private static  final int FINDTHEME = 4;
    private  static  final int COMPARTIMENT = 2;
    private static  final int CARTE = 3;
    BaseFlashCard base;
    private static final UriMatcher matcher = new UriMatcher(UriMatcher.NO_MATCH);
    static {
        matcher.addURI(authority,"theme",THEME);
        matcher.addURI(authority,"compartiment",COMPARTIMENT);
        matcher.addURI(authority,"carte",CARTE);
        matcher.addURI(authority,"findTheme/*",FINDTHEME);
        matcher.addURI(authority,"findComp",COMPARTIMENT);

    }

    public FCContentProvider() {}

    @Override
    public int delete(Uri uri, String selection, String[] selectionArgs) {
        // Implement this to handle requests to delete one or more rows.
        throw new UnsupportedOperationException("Not yet implemented");
    }

    @Override
    public String getType(Uri uri) {
        // TODO: Implement this to handle requests for the MIME type of the data
        // at the given URI.
        throw new UnsupportedOperationException("Not yet implemented");
    }

    @Override
    public Uri insert(Uri uri, ContentValues values) {
        SQLiteDatabase db = base.getWritableDatabase();
        int code =  matcher.match(uri);
        Uri.Builder builder = new Uri.Builder();
        long id;

        switch(code) {
            case THEME:
                id=db.insertOrThrow("theme", null, values);
                break;
            case COMPARTIMENT:
                id=db.insertOrThrow("compartiment", null, values);
                break;
            case CARTE:
                id=db.insertOrThrow("carte", null, values);
                break;
            default:throw new UnsupportedOperationException("Erreur insert content provider");
        }
        builder.authority(authority);
        builder = ContentUris.appendId(builder, id);
        return builder.build();
    }

    @Override
    public boolean onCreate() {
        base = new BaseFlashCard(this.getContext());
        return true;
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection,
                        String[] selectionArgs, String sortOrder) {
        SQLiteDatabase db = base.getReadableDatabase();
        int code =  matcher.match(uri);
        Cursor dbCursor;
        String q;
        switch(code) {
            case THEME:

                q = "SELECT * FROM theme";

                dbCursor = db.rawQuery(q, null);
                return dbCursor;
            case COMPARTIMENT:
                q = "SELECT * FROM compartiment";

                dbCursor = db.rawQuery(q, null);
                return dbCursor;
            case CARTE:
                q = "SELECT * FROM carte";

                dbCursor = db.rawQuery(q, null);
                return dbCursor;
            case FINDTHEME:
                List<String> l= uri.getPathSegments();
                String p = l.get(1);
                q = "SELECT * FROM theme";
                 dbCursor =db.rawQuery(q, null);
                return dbCursor;

            default:
                throw new UnsupportedOperationException("Exception");
        }
    }

    @Override
    public int update(Uri uri, ContentValues values, String selection,
                      String[] selectionArgs) {
        // TODO: Implement this to handle requests to update one or more rows.
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
