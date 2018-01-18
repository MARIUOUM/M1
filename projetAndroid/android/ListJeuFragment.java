package com.example.binta.cartesmemoire;





import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;

import android.support.v4.app.ListFragment;
import android.support.v4.app.LoaderManager;
import android.support.v4.content.CursorLoader;
import android.support.v4.content.Loader;
import android.support.v4.widget.SimpleCursorAdapter;
import android.util.Log;


/**
 *
 * Activities that contain this fragment must implement the
 * {@link ListJeuFragment.OnFragmentInteractionListener} interface
 * to handle interaction events.
 * Use the {@link ListJeuFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ListJeuFragment extends ListFragment implements LoaderManager.LoaderCallbacks<Cursor>{
    // TODO: Rename parameter arguments, choose names that match
    // the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
    private static final String ARG_PARAM1 = "param1";
    private static final String ARG_PARAM2 = "param2";


    private SimpleCursorAdapter mAdapter;
    private static String authority = "com.example.binta.flshCrdProvider";

    // TODO: Rename and change types of parameters



    public ListJeuFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment ListJeuFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static ListJeuFragment newInstance(String param1, String param2) {
        ListJeuFragment fragment = new ListJeuFragment();

        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.d("oncrate","OK");
        super.onCreate(savedInstanceState);

        mAdapter = new SimpleCursorAdapter(getActivity(),
                android.R.layout.simple_list_item_2, null,
                new String[] {"themetext"},
                new int[] { android.R.id.text1}, 0);
        setListAdapter(mAdapter);

        getLoaderManager().initLoader(0, null, this);

    }


    public Loader<Cursor> onCreateLoader(int id, Bundle args) {
        Uri uri = (new Uri.Builder()).scheme("content")
                .authority(authority)
                .appendPath("theme")
                .build();
        Log.d("OncreateLoader", "onCreateLoader uri=" + uri.toString());
        return new CursorLoader(getActivity(), uri,
                new String[]{"_id", "themetext"},
                null, null, null);
    }

    public void onLoadFinished(Loader<Cursor> loader, Cursor data) {

        mAdapter.swapCursor(data);
        if (data != null) {
            Log.d("finished", "load finished taille=" + data.getCount() + "");
        } else {
            Log.d("finished", "load finished data null");
        }
    }

    public void onLoaderReset(Loader<Cursor> loader) {

        mAdapter.swapCursor(null);

    }




    /*@Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_list_jeu, container, false);
    }

    // TODO: Rename method, update argument and hook method into UI event
    public void onButtonPressed(Uri uri) {
        if (mListener != null) {
            mListener.onFragmentInteraction(uri);
        }
    }*/

   /* @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if (context instanceof OnFragmentInteractionListener) {
            mListener = (OnFragmentInteractionListener) context;
        } else {
            throw new RuntimeException(context.toString()
                    + " must implement OnFragmentInteractionListener");
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }*/

    /**
     * This interface must be implemented by activities that contain this
     * fragment to allow an interaction in this fragment to be communicated
     * to the activity and potentially other fragments contained in that
     * activity.
     * <p>
     * See the Android Training lesson <a href=
     * "http://developer.android.com/training/basics/fragments/communicating.html"
     * >Communicating with Other Fragments</a> for more information.
     */
    public interface OnFragmentInteractionListener {
        // TODO: Update argument type and name
        void onFragmentInteraction(Uri uri);
    }
}
