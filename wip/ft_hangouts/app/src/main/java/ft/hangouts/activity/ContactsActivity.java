package ft.hangouts.activity;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ListView;

import ft.hangouts.Constants;
import ft.hangouts.R;
import ft.hangouts.activity.base.TrackedActivity;
import ft.hangouts.adapter.ContactAdapter;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.util.ActionBarColorUtil;

public class ContactsActivity extends TrackedActivity {

    public static final String[] PERMISSIONS = new String[]{
            Manifest.permission.RECEIVE_SMS,
            Manifest.permission.SEND_SMS,
            Manifest.permission.CALL_PHONE,
    };

    private static ContactsActivity sInstance;

    private ListView mListView;

    private ContactAdapter mContactAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contacts);

        mListView = findViewById(R.id.listView);

        ActionBarColorUtil.apply(this);

        mContactAdapter = new ContactAdapter(this, new DatabaseHelper(this));
        mContactAdapter.refresh();

        mListView.setAdapter(mContactAdapter);

        requestPermissions();

        sInstance = this;
    }

    @Override
    protected void onDestroy() {
        sInstance = null;

        super.onDestroy();
    }

    public void requestPermissions() {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
            return;
        }

        boolean granted = true;
        for (String permission : PERMISSIONS) {
            granted &= checkSelfPermission(permission) == PackageManager.PERMISSION_GRANTED;
        }

        if (granted) {
            // mPermissionRequiredSnackbar.dismiss();
        } else {
            // mPermissionRequiredSnackbar.show();

            requestPermissions(PERMISSIONS, Constants.REQUEST_CODE_PERMISSION);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_contacts, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_add: {
                ContactEditorActivity.start(this, Constants.REQUEST_CODE_CONTACT_ACTIVITY, null);
                return true;
            }

            case R.id.action_settings: {
                startActivity(new Intent(this, SettingsActivity.class));
                return true;
            }
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onResume() {
        ActionBarColorUtil.apply(this);

        super.onResume();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == Constants.REQUEST_CODE_CONTACT_ACTIVITY) {
            switch (resultCode) {
                case Constants.RESULT_CODE_EDITED: {
                    Contact contact = (Contact) data.getSerializableExtra(Constants.KEY_CONTACT);
                    mContactAdapter.remove(contact);
                    mContactAdapter.insert(contact, 0);

                    break;
                }

                case Constants.RESULT_CODE_REMOVED: {
                    Contact contact = (Contact) data.getSerializableExtra(Constants.KEY_CONTACT);
                    mContactAdapter.remove(contact);

                    break;
                }
            }
        }

        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        if (Constants.REQUEST_CODE_PERMISSION == requestCode) {
            boolean granted = true;
            for (int grantResult : grantResults) {
                granted &= grantResult == PackageManager.PERMISSION_GRANTED;
            }

            if (granted) {
                // mPermissionRequiredSnackbar.dismiss();
            } else {
                new Handler(Looper.getMainLooper()).postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        // mPermissionRequiredSnackbar.show();
                    }
                }, 500);
            }
        }

        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    public ContactAdapter getContactAdapter() {
        return mContactAdapter;
    }

    public static ContactsActivity getInstance() {
        return sInstance;
    }
}