package com.example.jnitoast;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {
    /** Called when the activity is first created. */
	
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.main);
        
        Button btn = (Button)findViewById(R.id.btn);
        btn.setOnClickListener(new View.OnClickListener() {
				
			@Override
			public void onClick(View v) {
				CharSequence text = "JNIからToast表示";
				displayToast(text);
			}
		});
        
    }
    
    public native void displayToast(CharSequence charseq);

    static {
        System.loadLibrary("jnitoast");
    	}
    
}