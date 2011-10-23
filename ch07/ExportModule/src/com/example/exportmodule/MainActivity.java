package com.example.exportmodule;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        StringBuffer buf = new StringBuffer();
        
        TextView  tv = new TextView(this);
        
        String str = "fooval="+fooval() + " foofunc="+foofunc();
        tv.setText(str);
        setContentView(tv);
    }

    public native int fooval();
    public native int foofunc();
    
    static {
        System.loadLibrary("bar");
    }


}