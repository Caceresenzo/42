package ft.hangouts.activity;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.coordinatorlayout.widget.CoordinatorLayout;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import java.util.Arrays;

import ft.hangouts.R;
import ft.hangouts.adapter.ContactAdapter;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.util.ActionBarColorUtil;

public class MainActivity extends AppCompatActivity {

    public static final int REQUEST_CODE_PERMISSION = 1;
    public static final int REQUEST_CODE_CONTACT_EDITOR = 2;

    public static final String[] PERMISSIONS = new String[] {
            Manifest.permission.RECEIVE_SMS,
            Manifest.permission.CALL_PHONE,
    };

    private static MainActivity sInstance;

    private CoordinatorLayout mCoordinatorLayout;
    private Toolbar mToolbar;
    private RecyclerView mRecyclerView;
    private FloatingActionButton mFloatingActionButton;

    private Snackbar mPermissionRequiredSnackbar;

    private ContactAdapter mContactAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mCoordinatorLayout = findViewById(R.id.coordinatorLayout);
        mToolbar = findViewById(R.id.toolbar);
        mRecyclerView = findViewById(R.id.recyclerView);
        mFloatingActionButton = findViewById(R.id.floatingActionButton);

        setSupportActionBar(mToolbar);

        ActionBarColorUtil.apply(this);

        mContactAdapter = new ContactAdapter(new DatabaseHelper(this), this);
        mContactAdapter.refresh();

        mRecyclerView.setAdapter(mContactAdapter);
        mRecyclerView.setLayoutManager(new LinearLayoutManager(this));

        mFloatingActionButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ContactEditorActivity.start(MainActivity.this, REQUEST_CODE_CONTACT_EDITOR, null);
            }
        });

        mPermissionRequiredSnackbar = Snackbar
                .make(mCoordinatorLayout, R.string.permission_required, Snackbar.LENGTH_INDEFINITE)
                .setAction(R.string.permission_authorize, new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        requestPermissions();
                    }
                });

        requestPermissions();

        sInstance = this;
    }

    @Override
    protected void onDestroy() {
        sInstance = null;

        super.onDestroy();
    }

    public void requestPermissions() {
        boolean granted = true;
        for (String permission : PERMISSIONS) {
            granted &= ContextCompat.checkSelfPermission(this, permission) == PackageManager.PERMISSION_GRANTED;
        }

        if (granted) {
            mPermissionRequiredSnackbar.dismiss();
        } else {
            mPermissionRequiredSnackbar.show();

            ActivityCompat.requestPermissions(this, PERMISSIONS, REQUEST_CODE_PERMISSION);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            startActivity(new Intent(this, SettingsActivity.class));

            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onResume() {
        ActionBarColorUtil.apply(this);

        super.onResume();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        if (requestCode == REQUEST_CODE_CONTACT_EDITOR) {
            mContactAdapter.refresh();
        }

        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (REQUEST_CODE_PERMISSION == requestCode) {
            boolean granted = true;
            for (int grantResult : grantResults) {
                granted &= grantResult == PackageManager.PERMISSION_GRANTED;
            }

            if (granted) {
                mPermissionRequiredSnackbar.dismiss();
            } else {
                new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        mPermissionRequiredSnackbar.show();
                    }
                }, 500);
            }
        }

        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    public ContactAdapter getContactAdapter() {
        return mContactAdapter;
    }

    public static MainActivity getInstance() {
        return sInstance;
    }
}