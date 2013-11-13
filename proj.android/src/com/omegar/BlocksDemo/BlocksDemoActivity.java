/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.omegar.BlocksDemo;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.text.Html;
import android.widget.Toast;

public class BlocksDemoActivity extends Cocos2dxActivity {
	
	static Context selfContext = null;

	public static boolean sendEmail(String[] recipients, String messageText, boolean isHtml, String subject, String attachment) {
		Intent intent = new Intent(Intent.ACTION_SEND);
		if (isHtml) {
			intent.setType("text/html");
		    intent.putExtra(Intent.EXTRA_TEXT, Html.fromHtml(messageText));
		} else {
			intent.setType("text/plain");
		    intent.putExtra(Intent.EXTRA_TEXT, messageText);
		}
		intent.putExtra(Intent.EXTRA_EMAIL, recipients);
		intent.putExtra(Intent.EXTRA_SUBJECT, subject);
		if (attachment.length() > 0) {
			intent.putExtra(Intent.EXTRA_STREAM, attachment);
		}
	    try {
	    	selfContext.startActivity(Intent.createChooser(intent, "Choose an Email client :"));
	    } catch (android.content.ActivityNotFoundException ex) {
	        Toast.makeText(selfContext, "No any e-mail client installed", Toast.LENGTH_SHORT).show();
	        return false;
	    }
        return true;
	}

	protected void onCreate(Bundle savedInstanceState) {
		selfContext = getContext();
		super.onCreate(savedInstanceState);
	}
	
	@Override
	protected void onPause() {
		selfContext = null;
		super.onPause();
	}
	
	@Override
	protected void onResume() {
		selfContext = getContext();
		super.onResume();
	}
	
    static {
        System.loadLibrary("game");
    }
}
