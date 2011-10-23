package com.example.playmusic;

import com.example.playmusic.R;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	
    static AssetManager assetManager;
    static boolean isPlayingAsset = false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
	    
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        assetManager = getAssets();

        // initialize native audio system

        createEngine();
        createBufferQueueAudioPlayer();

        // initialize button click handlers

        
        ((Button) findViewById(R.id.playbgm)).setOnClickListener(new OnClickListener() {
                boolean created = false;
                public void onClick(View view) {
                    if (!created) {
                        created = createAssetAudioPlayer(assetManager, "background.mp3");
                    }
                    if (created) {
                        isPlayingAsset = !isPlayingAsset;
                        setPlayingAssetAudioPlayer(isPlayingAsset);
                    }
                }
            });

    }
    
    public static native void createEngine();
    public static native void createBufferQueueAudioPlayer();
    public static native boolean createAssetAudioPlayer(AssetManager assetManager, String filename);
    public static native void setPlayingAssetAudioPlayer(boolean isPlaying);

}