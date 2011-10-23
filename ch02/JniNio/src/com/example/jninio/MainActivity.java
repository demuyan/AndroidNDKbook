package com.example.jninio;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		ByteBuffer byteBuffer = ByteBuffer.allocateDirect(10);
		byteBuffer.order(ByteOrder.LITTLE_ENDIAN);

		int a = 30;
		short b = 20;
		byte c = 10;

		byteBuffer.putInt(0, a);
		byteBuffer.putShort(4, b);
		byteBuffer.put(6, c);
		setByteBuffer(byteBuffer);

		TextView tv = new TextView(this);

		StringBuffer strBuf = new StringBuffer();

		strBuf.append("a="+byteBuffer.getInt(0) + "\n");
		strBuf.append("b="+byteBuffer.getShort(4) + "\n");
		strBuf.append("c="+byteBuffer.get(6) + "\n");

		tv.setText(strBuf.toString());
		setContentView(tv);
	}

	public native int setByteBuffer(java.nio.Buffer byteBuffer);

	static {
		System.loadLibrary("jninio");
	}

}