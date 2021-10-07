package ft.hangouts.util;

import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Build;
import android.view.Window;
import android.view.WindowManager;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.ColorUtils;

public class ActionBarColorUtil {

    public static void apply(AppCompatActivity activity) {
        int color = Color.MAGENTA;
        int darken = ColorUtils.blendARGB(color, Color.BLACK, 0.2f);

        ActionBar actionBar = activity.getSupportActionBar();
        if (actionBar == null) {
            return;
        }

        actionBar.setBackgroundDrawable(new ColorDrawable(color));

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            Window window = activity.getWindow();
            window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
            window.setStatusBarColor(darken);
        }
    }

}