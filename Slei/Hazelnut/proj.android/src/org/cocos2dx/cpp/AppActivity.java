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

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.annotation.TargetApi;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

public class AppActivity extends Cocos2dxActivity {
	private static AppActivity _appActiviy;

	// Ads
	private AdView adView;
	private AdView adViewBottom;
	private AdView adViewScreen;
	private Button adViewScreenSkipAdButton;
	// private InterstitialAd iAd;

	// Admob Banner IDs
	private static final String AD_UNIT_ID = "ca-app-pub-9638672228116696/3546955560";
	private static final String AD_UNIT_BOTTOM_ID = "ca-app-pub-9638672228116696/5540979969";
	private static final String AD_UNIT_FULL_ID = "ca-app-pub-9638672228116696/4508227563";
	private static final boolean USED_FOR_PRODUCTION = false;

	// Helper get display screen to avoid deprecated function use
	private Point getDisplaySize(Display d) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
			return getDisplaySizeGE11(d);
		}
		return getDisplaySizeLT11(d);
	}

	/**
	 * This method converts device specific pixels to density independent
	 * pixels.
	 * 
	 * @param px
	 *            A value in px (pixels) unit. Which we need to convert into db
	 * @param context
	 *            Context to get resources and device specific display metrics
	 * @return A float value to represent dp equivalent to px value
	 */
	public static float convertPixelsToDp(float px, Context context) {
		Resources resources = context.getResources();
		DisplayMetrics metrics = resources.getDisplayMetrics();
		float dp = px / (metrics.densityDpi / 160f);
		return dp;
	}

	@TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
	private Point getDisplaySizeGE11(Display d) {
		Point p = new Point(0, 0);
		d.getSize(p);
		return p;
	}

	private Point getDisplaySizeLT11(Display d) {
		try {
			Method getWidth = Display.class.getMethod("getWidth",
					new Class[] {});
			Method getHeight = Display.class.getMethod("getHeight",
					new Class[] {});
			return new Point(
					((Integer) getWidth.invoke(d, (Object[]) null)).intValue(),
					((Integer) getHeight.invoke(d, (Object[]) null)).intValue());
		} catch (NoSuchMethodException e2) // None of these exceptions should
											// ever occur.
		{
			return new Point(-1, -1);
		} catch (IllegalArgumentException e2) {
			return new Point(-2, -2);
		} catch (IllegalAccessException e2) {
			return new Point(-3, -3);
		} catch (InvocationTargetException e2) {
			return new Point(-4, -4);
		}
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		int displayWidth = getDisplaySize(getWindowManager()
				.getDefaultDisplay()).x;
		int displayHeight = getDisplaySize(getWindowManager()
				.getDefaultDisplay()).y;

		initAdView(displayWidth);
		initAdViewBottom();
		initAdViewScreen(displayWidth, displayHeight);

		_appActiviy = this;

		// always hide the ad views at start or if coming from standby
		hideAd();
		hideAdBottom();
		hideAdScreen();

	}

	private void initAdView(int displayWidth) {
		// Position adView at the top
		LinearLayout.LayoutParams adViewLayoutParams = new LinearLayout.LayoutParams(
				displayWidth, LinearLayout.LayoutParams.WRAP_CONTENT);

		adView = new AdView(this);
		adView.setAdSize(AdSize.BANNER);
		adView.setAdUnitId(AD_UNIT_ID);

		AdRequest adRequest = null;
		if (USED_FOR_PRODUCTION) {
			adRequest = new AdRequest.Builder().build();
		} else {
			adRequest = new AdRequest.Builder()
					.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
					.addTestDevice("81ACDEAF4A1581BCA1CC8C3F7B17AF2A").build();
		}

		adView.loadAd(adRequest);
		adView.setBackgroundColor(Color.BLACK);
		adView.setBackgroundColor(0);

		addContentView(adView, adViewLayoutParams);
	}

	private void initAdViewBottom() {
		// Position adView at the bottom
		FrameLayout.LayoutParams adParamsBottom = new FrameLayout.LayoutParams(
				FrameLayout.LayoutParams.WRAP_CONTENT,
				FrameLayout.LayoutParams.WRAP_CONTENT,
				android.view.Gravity.BOTTOM
						| android.view.Gravity.CENTER_HORIZONTAL);

		adViewBottom = new AdView(this);
		adViewBottom.setAdSize(AdSize.LARGE_BANNER);
		adViewBottom.setAdUnitId(AD_UNIT_BOTTOM_ID);

		AdRequest adRequestBottom = null;
		if (USED_FOR_PRODUCTION) {
			adRequestBottom = new AdRequest.Builder().build();
		} else {
			adRequestBottom = new AdRequest.Builder()
					.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
					.addTestDevice("81ACDEAF4A1581BCA1CC8C3F7B17AF2A").build();
		}

		adViewBottom.loadAd(adRequestBottom);
		adViewBottom.setBackgroundColor(Color.BLACK);
		adViewBottom.setBackgroundColor(0);

		addContentView(adViewBottom, adParamsBottom);
	}

	private void initAdViewScreen(int displayWidth, int displayHeight) {
		// Position adView in the middle
		FrameLayout.LayoutParams adParamsScreen = new FrameLayout.LayoutParams(
				FrameLayout.LayoutParams.MATCH_PARENT,
				FrameLayout.LayoutParams.MATCH_PARENT,
				android.view.Gravity.CENTER_VERTICAL
						| android.view.Gravity.CENTER_HORIZONTAL);

		adViewScreen = new AdView(this);
		adViewScreen.setAdSize(new AdSize((int) (convertPixelsToDp(
				displayWidth / 100 * 95, this)), (int) (convertPixelsToDp(
				displayHeight / 100 * 95, this))));
		// adViewScreen.setAdSize(AdSize.LARGE_BANNER);
		adViewScreen.setAdUnitId(AD_UNIT_FULL_ID);

		AdRequest adRequestScreen = null;
		if (USED_FOR_PRODUCTION) {
			adRequestScreen = new AdRequest.Builder().build();
		} else {
			adRequestScreen = new AdRequest.Builder()
					.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
					.addTestDevice("81ACDEAF4A1581BCA1CC8C3F7B17AF2A").build();
		}

		adViewScreen.loadAd(adRequestScreen);
		adViewScreen.setBackgroundColor(Color.BLACK);
		adViewScreen.setBackgroundColor(0);

		addContentView(adViewScreen, adParamsScreen);

		// Position adView button at the bottom
		FrameLayout.LayoutParams adParamsScreenButton = new FrameLayout.LayoutParams(
				FrameLayout.LayoutParams.WRAP_CONTENT,
				FrameLayout.LayoutParams.WRAP_CONTENT,
				android.view.Gravity.BOTTOM
						| android.view.Gravity.CENTER_HORIZONTAL);

		adViewScreenSkipAdButton = new Button(this);
		adViewScreenSkipAdButton.setText("Skip Ad");
		adViewScreenSkipAdButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				AppActivity.hideAdScreen();
			}
		});

		addContentView(adViewScreenSkipAdButton, adParamsScreenButton);
	}

	public static void hideAd() {
		_appActiviy.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				Log.i("adview", "hideAd");
				if (_appActiviy.adView.isEnabled())
					_appActiviy.adView.setEnabled(false);
				if (_appActiviy.adView.getVisibility() != 4)
					_appActiviy.adView.setVisibility(View.INVISIBLE);
			}
		});

	}

	public static void showAd() {
		_appActiviy.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				Log.i("adview", "showAd");
				if (!_appActiviy.adView.isEnabled())
					_appActiviy.adView.setEnabled(true);
				if (_appActiviy.adView.getVisibility() == 4)
					_appActiviy.adView.setVisibility(View.VISIBLE);
			}
		});

	}

	public static void hideAdBottom() {
		_appActiviy.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				Log.i("adviewBottom", "hideAd");
				if (_appActiviy.adViewBottom.isEnabled())
					_appActiviy.adViewBottom.setEnabled(false);
				if (_appActiviy.adViewBottom.getVisibility() != 4)
					_appActiviy.adViewBottom.setVisibility(View.INVISIBLE);
			}
		});

	}

	public static void showAdBottom() {
		_appActiviy.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				Log.i("adviewBottom", "showAd");
				if (!_appActiviy.adViewBottom.isEnabled())
					_appActiviy.adViewBottom.setEnabled(true);
				if (_appActiviy.adViewBottom.getVisibility() == 4)
					_appActiviy.adViewBottom.setVisibility(View.VISIBLE);
			}
		});

	}

	public static void hideAdScreen() {
		_appActiviy.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				Log.i("adviewScreen", "hideAd");
				if (_appActiviy.adViewScreen.isEnabled())
					_appActiviy.adViewScreen.setEnabled(false);
				if (_appActiviy.adViewScreen.getVisibility() != 4)
					_appActiviy.adViewScreen.setVisibility(View.INVISIBLE);
				_appActiviy.adViewScreenSkipAdButton
						.setVisibility(View.INVISIBLE);
			}
		});

	}

	public static void showAdScreen() {
		_appActiviy.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// if (_appActiviy.iAd.isLoaded()) {
				// _appActiviy.iAd.show();
				// }

				Log.i("adviewScreen", "showAd");
				if (!_appActiviy.adViewScreen.isEnabled())
					_appActiviy.adViewScreen.setEnabled(true);
				if (_appActiviy.adViewScreen.getVisibility() == 4)
					_appActiviy.adViewScreen.setVisibility(View.VISIBLE);
				_appActiviy.adViewScreenSkipAdButton
						.setVisibility(View.VISIBLE);
			}
		});

	}

	@Override
	protected void onResume() {
		super.onResume();
		if (adView != null) {
			adView.resume();
		}
		if (adViewBottom != null) {
			adViewBottom.resume();
		}
		if (adViewScreen != null) {
			adViewScreen.resume();
		}
	}

	@Override
	protected void onPause() {
		if (adView != null) {
			adView.pause();
		}
		if (adViewBottom != null) {
			adViewBottom.pause();
		}
		if (adViewScreen != null) {
			adViewScreen.pause();
		}
		super.onPause();
	}

	@Override
	protected void onDestroy() {
		adView.destroy();
		adViewBottom.destroy();
		adViewScreen.destroy();
		super.onDestroy();
	}

}
