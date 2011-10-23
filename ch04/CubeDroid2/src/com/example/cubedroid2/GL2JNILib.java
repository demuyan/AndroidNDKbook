package com.example.cubedroid2;

// Wrapper for native library

public class GL2JNILib {

     static {
         System.loadLibrary("cubedroid2");
     }

    /**
     * @param width the current view width
     * @param height the current view height
     */
     public static native void init(int width, int height);
     public static native void step();
}
