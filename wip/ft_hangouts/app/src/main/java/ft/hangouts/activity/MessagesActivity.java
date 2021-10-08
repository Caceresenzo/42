package ft.hangouts.activity;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;

import ft.hangouts.R;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.util.ActionBarColorUtil;

public class MessagesActivity extends AppCompatActivity {

    public static final String KEY_CONTACT = "contact";

    private static MessagesActivity sInstance;

    private Contact mContact;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_messages);

        mContact = (Contact) getIntent().getSerializableExtra(KEY_CONTACT);
        if (mContact == null) {
            finish();
            return;
        }

        ActionBarColorUtil.apply(this);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setNameInActionBar();

        sInstance = this;
    }

    private void setNameInActionBar() {
        String title = mContact.getName();
        String subtitle = null;

        if (TextUtils.isEmpty(title)) {
            title = mContact.getPhone();
        } else {
            subtitle = mContact.getPhone();
        }

        getSupportActionBar().setTitle(title);
        getSupportActionBar().setSubtitle(subtitle);
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);

        outState.putSerializable(KEY_CONTACT, mContact);
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        mContact = (Contact) savedInstanceState.getSerializable(KEY_CONTACT);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_messages, menu);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home: {
                finish();

                return true;
            }

            case R.id.action_show_contact: {
                ContactEditorActivity.start(this, 0, mContact);
                return true;
            }
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        sInstance = null;
    }

    public static MessagesActivity getInstance() {
        return sInstance;
    }

    public static void start(Activity context, int requestCode, Contact contact) {
        Intent intent = new Intent(context, MessagesActivity.class);
        intent.putExtra(KEY_CONTACT, contact);

        context.startActivityForResult(intent, requestCode);
    }
}