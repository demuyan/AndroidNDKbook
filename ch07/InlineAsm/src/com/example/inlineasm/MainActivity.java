package com.example.inlineasm;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        StringBuffer buf = new StringBuffer();
        
        TextView  tv = new TextView(this);

        int a = 10;
        int b = 2;

        int val = addVals(a, b);
        buf.append("a+b="+String.valueOf(val)+"\n"); 
        val = subVals(a, b);
        buf.append("a-b="+String.valueOf(val)+"\n"); 
        val = mulVals(a, b);
        buf.append("a*b="+String.valueOf(val)+"\n"); 
        val = divVals(a, b);
        buf.append("a/b="+String.valueOf(val)+"\n"); 
        
        tv.setText( buf.toString() );
        setContentView(tv);
    }

    public native int addVals(int a, int b);
    public native int subVals(int a, int b);
    public native int mulVals(int a, int b);
    public native int divVals(int a, int b);

    static {
        System.loadLibrary("inlineasm");
    }
}