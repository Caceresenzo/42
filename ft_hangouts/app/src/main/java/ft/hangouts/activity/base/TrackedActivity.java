package ft.hangouts.activity.base;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Date;

import ft.hangouts.R;

public abstract class TrackedActivity extends Activity {

    private static final String KEY_PAUSED = "paused";
    private static final String KEY_PAUSED_AT = "paused_at";

    private boolean mPaused;
    private Date mPausedAt;

    @Override
    protected void onPause() {
        mPaused = true;
        mPausedAt = new Date();

        super.onPause();
    }

    @Override
    protected void onResume() {
        if (mPaused && mPausedAt != null) {
            String clazz = getClass().getSimpleName();
            String at = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(mPausedAt);
            double pausedFor = (new Date().getTime() - mPausedAt.getTime()) / 1000.0;

            String message = getString(R.string.pause_tracking_summary, clazz, at, pausedFor);
            Toast.makeText(this, message, Toast.LENGTH_LONG).show();
        }

        mPaused = false;
        mPausedAt = null;

        super.onResume();
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        outState.putBoolean(KEY_PAUSED, mPaused);
        outState.putLong(KEY_PAUSED_AT, mPausedAt != null ? mPausedAt.getTime() : -1);

        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        mPaused = savedInstanceState.getBoolean(KEY_PAUSED);

        long at = savedInstanceState.getLong(KEY_PAUSED_AT, -1);
        if (at != -1) {
            mPausedAt = new Date(at);
        } else {
            mPausedAt = null;
        }

        super.onRestoreInstanceState(savedInstanceState);
    }
}