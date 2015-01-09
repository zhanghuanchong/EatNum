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

import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

public class AppActivity extends Cocos2dxActivity {
	private AdView adView;
	private static boolean bShowAd = false;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// 创建adView。
		adView = new AdView(this);
		adView.setAdUnitId("ca-app-pub-5072970286349933/3457682424");
		adView.setAdSize(AdSize.BANNER);
		
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

		// 启动一般性请求。
		AdRequest adRequest = new AdRequest.Builder().build();

		// 在adView中加载广告请求。
		adView.loadAd(adRequest);
	}

	@Override
	public void onPause() {
		adView.pause();
		super.onPause();
	}

	@Override
	public void onResume() {
		super.onResume();
		adView.resume();
	}

	@Override
	public void onDestroy() {
		adView.destroy();
		super.onDestroy();
	}
}
