package ft.hangouts.activity;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import ft.hangouts.R;
import ft.hangouts.adapter.MessageAdapter;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.util.ActionBarColorUtil;

public class MessagesActivity extends AppCompatActivity {

    public static final String KEY_CONTACT = "contact";
    public static final String TELEPHONE_SCHEMA = "tel:";

    private static MessagesActivity sInstance;

    private RecyclerView recyclerView;

    private Contact mContact;
    private MessageAdapter mMessageAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_messages);

        recyclerView = findViewById(R.id.recyclerView);

        mContact = (Contact) getIntent().getSerializableExtra(KEY_CONTACT);
        if (mContact == null) {
            finish();
            return;
        }

        ActionBarColorUtil.apply(this);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setNameInActionBar();

        mMessageAdapter = new MessageAdapter(new DatabaseHelper(this));
        mMessageAdapter.refresh();

        recyclerView.setAdapter(mMessageAdapter);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        int last = mMessageAdapter.getItemCount() - 1;
        if (last != -1) {
            recyclerView.scrollToPosition(last);
        }

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

            case R.id.action_call: {
                call();
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

    public void call() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CALL_PHONE) == PackageManager.PERMISSION_GRANTED) {
            Intent intent = new Intent(Intent.ACTION_CALL);
            intent.setData(Uri.parse(TELEPHONE_SCHEMA + mContact.getPhone()));

            startActivity(intent);
        } else {
            Toast.makeText(this, R.string.permission_not_given, Toast.LENGTH_SHORT).show();
        }
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