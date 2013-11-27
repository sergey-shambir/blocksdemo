package com.omegar.BlocksDemo;

import java.io.File;

import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.text.Html;
import android.widget.Toast;
import android.support.v4.content.FileProvider;

public class PlatformUtils {
	
	private static Context context() {
		return BlocksDemoActivity.selfContext;
	}

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
			File attachedFile = new File(attachment);
			Uri contentUri = FileProvider.getUriForFile(context(), "com.omegar.fileprovider", attachedFile);
			intent.putExtra(Intent.EXTRA_STREAM, contentUri);
			intent.setFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
		}
	    try {
	    	context().startActivity(Intent.createChooser(intent, "Choose an Email client :"));
	    } catch (android.content.ActivityNotFoundException ex) {
	        Toast.makeText(context(), "No any e-mail client installed", Toast.LENGTH_SHORT).show();
	        return false;
	    }
        return true;
	}
	
	public static String getApkVersion() {
		try {
			PackageInfo pInfo = context().getPackageManager().getPackageInfo(context().getPackageName(), 0);
			return pInfo.versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return "Unknown";
	}
	
	public static String getApkVersionCode() {
		try {
			PackageInfo pInfo = context().getPackageManager().getPackageInfo(context().getPackageName(), 0);
			return String.valueOf(pInfo.versionCode);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return "Unknown";
	}
	
	public static String getSystemVersion() {
		return "Android " + android.os.Build.VERSION.RELEASE;
	}

    public static String getDeviceName() {
        return android.os.Build.PRODUCT + " (" + android.os.Build.MODEL + ") by " + android.os.Build.MANUFACTURER;
    }
	
	public static String getApkName() {
		try {
			PackageInfo pInfo = context().getPackageManager().getPackageInfo(context().getPackageName(), 0);
			return pInfo.packageName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return "Unknown";
	}

}
