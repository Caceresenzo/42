package ft.hangouts.activity;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.Date;

import ft.hangouts.R;
import ft.hangouts.adapter.MessageAdapter;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.model.Message;
import ft.hangouts.util.ActionBarColorUtil;

public class MessagesActivity extends AppCompatActivity {

    public static final int REQUEST_CODE_CONTACT_EDITOR = MainActivity.REQUEST_CODE_CONTACT_EDITOR;

    public static final String KEY_CONTACT = "contact";

    public static final String TELEPHONE_SCHEMA = "tel:";

    private static MessagesActivity sInstance;

    private RecyclerView mRecyclerView;
    private EditText mInputEditText;
    private ImageButton mSendImageButton;

    private Contact mContact;
    private MessageAdapter mMessageAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_messages);

        mRecyclerView = findViewById(R.id.recyclerView);
        mInputEditText = findViewById(R.id.message);
        mSendImageButton = findViewById(R.id.send);

        mContact = (Contact) getIntent().getSerializableExtra(KEY_CONTACT);
        if (mContact == null) {
            finish();
            return;
        }

        ActionBarColorUtil.apply(this);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        setNameInActionBar();

        mMessageAdapter = new MessageAdapter(new DatabaseHelper(this), mContact);
        mMessageAdapter.refresh();

        mRecyclerView.setAdapter(mMessageAdapter);
        mRecyclerView.setLayoutManager(new LinearLayoutManager(this));

        scrollToBottom();

        mInputEditText.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
            }

            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                mSendImageButton.setEnabled(s.length() != 0);
            }
        });

        mSendImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendMessage();
            }
        });

        sInstance = this;
    }

    private void setNameInActionBar() {
        getSupportActionBar().setTitle(mContact.getDisplayableTitle());
        getSupportActionBar().setSubtitle(mContact.getDisplayableSubtitle());
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
                ContactActivity.start(this, 0, mContact, false);
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

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        if (requestCode == REQUEST_CODE_CONTACT_EDITOR) {
            if (resultCode == ContactEditorActivity.RESULT_CODE_REMOVED) {
                finish();
            }
        }

        super.onActivityResult(requestCode, resultCode, data);
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

    private void sendMessage() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.SEND_SMS) == PackageManager.PERMISSION_GRANTED) {
            DatabaseHelper helper = new DatabaseHelper(this);

            Message message = helper.save(new Message()
                    .setContact(mContact)
                    .setSide(Message.SIDE_SEND)
                    .setAt(new Date())
                    .setBody(mInputEditText.getText().toString()));

            mInputEditText.setText(null);

            SmsManager smsManager = SmsManager.getDefault();
            smsManager.sendTextMessage(mContact.getPhone(), null, message.getBody(), null, null);

            add(message, true);
        } else {
            Toast.makeText(this, R.string.permission_not_given, Toast.LENGTH_SHORT).show();
        }
    }

    public void add(Message message) {
        if (message.getContactId() != mContact.getId()) {
            return;
        }

        boolean autoScroll = !mRecyclerView.canScrollVertically(1);

        add(message, autoScroll);
    }

    public void add(Message message, boolean scroll) {
        mMessageAdapter.add(message);

        if (scroll) {
            scrollToBottom();
        }
    }

    public void scrollToBottom() {
        int last = mMessageAdapter.getItemCount() - 1;
        if (last != -1) {
            mRecyclerView.scrollToPosition(last);
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