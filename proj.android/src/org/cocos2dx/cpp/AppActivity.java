/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
package org.cocos2dx.cpp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import cn.domob.android.ads.AdView;
import cn.domob.android.ads.InterstitialAd;
import cn.domob.android.ads.InterstitialAdListener;
import cn.domob.android.ads.AdManager.ErrorCode;


public class AppActivity extends Cocos2dxActivity {
	private AdView adView;
	private static InterstitialAd mInterstitialAd;
	private static Context context;
	private static String publisherID = "56OJwNvIuN5x24uPR1";
	private static boolean bShowAd = false;
	private static String apkURL = "http://t.cn/RZX66pv"; // http://wuruihong.com/eatnum.apk 
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		context = this;

		adView = new AdView(this, publisherID, "16TLuu_oApZpHNUOizHZOQ5s");		
        FrameLayout fl = (FrameLayout) ((ViewGroup)this.findViewById(android.R.id.content)).getChildAt(0);
        
        final LinearLayout layout = new LinearLayout(getContext());
        layout.setOrientation(LinearLayout.VERTICAL);
        this.setContentView(layout);
        
        LinearLayout.LayoutParams param = new LinearLayout.LayoutParams(
        		LinearLayout.LayoutParams.MATCH_PARENT,
        		LinearLayout.LayoutParams.WRAP_CONTENT,
        		1.0f);
        layout.addView(fl, param);

        final LinearLayout.LayoutParams param2 = new LinearLayout.LayoutParams(
        		LinearLayout.LayoutParams.MATCH_PARENT,
        		100);
        String result = "";
        URL url = null;
        HttpURLConnection connection = null;
        InputStreamReader in = null;
        try {
            url = new URL("http://wuruihong.com/eatnum.php");
//            url = new URL("http://wuruihong.com/eatnum.php?s=xiaomi");
//            url = new URL("http://wuruihong.com/eatnum.php?s=360");
            connection = (HttpURLConnection) url.openConnection();
            in = new InputStreamReader(connection.getInputStream());
            BufferedReader bufferedReader = new BufferedReader(in);
            StringBuffer strBuffer = new StringBuffer();
            String line = null;
            while ((line = bufferedReader.readLine()) != null) {
                strBuffer.append(line);
            }
            result = strBuffer.toString();
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (connection != null) {
                connection.disconnect();
            }
            if (in != null) {
                try {
                    in.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        if (result.equals("true")) {
        	bShowAd = true;
        	layout.addView(adView, param2);
        }

        mInterstitialAd = new InterstitialAd(this, publisherID, "16TLuu_oApZpHNUOi8KQzBTk");
		mInterstitialAd.setInterstitialAdListener(new InterstitialAdListener() {
			@Override
			public void onInterstitialAdReady() {
				Log.i("DomobSDKDemo", "onAdReady");
			}

			@Override
			public void onLandingPageOpen() {
				Log.i("DomobSDKDemo", "onLandingPageOpen");
			}

			@Override
			public void onLandingPageClose() {
				Log.i("DomobSDKDemo", "onLandingPageClose");
			}

			@Override
			public void onInterstitialAdPresent() {
				Log.i("DomobSDKDemo", "onInterstitialAdPresent");
			}

			@Override
			public void onInterstitialAdDismiss() {
				// Request new ad when the previous interstitial ad was closed.
				mInterstitialAd.loadInterstitialAd();
				Log.i("DomobSDKDemo", "onInterstitialAdDismiss");
			}

			@Override
			public void onInterstitialAdFailed(ErrorCode arg0) {
				Log.i("DomobSDKDemo", "onInterstitialAdFailed");				
			}

			@Override
			public void onInterstitialAdLeaveApplication() {
				Log.i("DomobSDKDemo", "onInterstitialAdLeaveApplication");
				
			}

			@Override
			public void onInterstitialAdClicked(InterstitialAd arg0) {
				Log.i("DomobSDKDemo", "onInterstitialAdClicked");
			}
		});
		mInterstitialAd.loadInterstitialAd();
	}

	public static void showInterstitialAd() {
		if (bShowAd) {
			Activity c = (Activity)context;
			c.runOnUiThread(new Runnable() {
			    @Override
			    public void run() {
					if (mInterstitialAd.isInterstitialAdReady()){
						mInterstitialAd.showInterstitialAd(context);
					} else {
						Log.i("DomobSDKDemo", "Interstitial Ad is not ready");
						mInterstitialAd.loadInterstitialAd();
					}
			    }
			});
		}
	}

	public static void sendMail() {
		final Activity c = (Activity)context;
		c.runOnUiThread(new Runnable() {
		    @Override
		    public void run() {
		    	Intent data=new Intent(Intent.ACTION_SENDTO);
		    	data.setData(Uri.parse("mailto:support@wuruihong.com"));
		    	data.putExtra(Intent.EXTRA_SUBJECT, c.getString(com.app4cn.eatnum.R.string.mail_subject));
		    	c.startActivity(data);
		    }
		});
	}
	
	public static void askForExit() {
		final Activity c = (Activity)context;
		c.runOnUiThread(new Runnable() {
		    @Override
		    public void run() {
				AlertDialog.Builder build = new AlertDialog.Builder(c);
				build.setTitle(c.getString(com.app4cn.eatnum.R.string.quit))
					  .setMessage(c.getString(com.app4cn.eatnum.R.string.quit_string))
					  .setPositiveButton(c.getString(com.app4cn.eatnum.R.string.yes), new DialogInterface.OnClickListener() {

						  @Override
						  public void onClick(DialogInterface dialog, int which) {
							  System.exit(0);
						  }
					  })
					  .setNegativeButton(c.getString(com.app4cn.eatnum.R.string.no), new DialogInterface.OnClickListener() {

						  @Override
						  public void onClick(DialogInterface dialog, int which) {
							  dialog.dismiss();
						  }
					  })
					  .show();
		    }
		});
	}
	
	public static void showActivities() {
		final Activity c = (Activity)context;
		c.runOnUiThread(new Runnable() {
		    @Override
		    public void run() {
		    	Intent sendIntent = new Intent();
		    	sendIntent.setAction(Intent.ACTION_SEND);
		    	sendIntent.putExtra(Intent.EXTRA_TEXT, c.getString(com.app4cn.eatnum.R.string.share_string) + AppActivity.apkURL);
		    	sendIntent.setType("text/plain");
		    	c.startActivity(sendIntent);
		    }
		});
	}
}
