package com.example.nativebitmap;

import android.app.Activity;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends Activity {
    private ImageView imageview1;
    private Bitmap bitmap;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        imageview1 = (ImageView)findViewById(R.id.imageview1);

        Resources r= getResources();
        bitmap = BitmapFactory.decodeResource(r, R.drawable.android_logo);
        imageview1.setImageBitmap(bitmap);
        
        Button btn = (Button)findViewById(R.id.button1);
        btn.setOnClickListener(new OnClickListener() {
           
           @Override
           public void onClick(View arg0) {
               reverseImage(bitmap);
               imageview1.setImageBitmap(bitmap);
           }
       });
    }
    
    public native int reverseImage(Bitmap bitmap);

    static {
        System.loadLibrary("nativebitmap");
    }

    
}