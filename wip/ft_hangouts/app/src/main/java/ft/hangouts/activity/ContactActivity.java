package ft.hangouts.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.google.android.material.appbar.CollapsingToolbarLayout;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.textfield.TextInputEditText;
import com.google.android.material.textfield.TextInputLayout;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.text.TextUtils;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import ft.hangouts.R;
import ft.hangouts.adapter.MessageAdapter;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.util.ActionBarColorUtil;

public class ContactActivity extends AppCompatActivity {

    public static final int REQUEST_CODE_CONTACT_EDITOR = MainActivity.REQUEST_CODE_CONTACT_EDITOR;

    public static final String KEY_CONTACT = "contact";
    public static final String KEY_MESSAGE_BUTTON = "message_button";

    private Toolbar mToolbar;
    private CollapsingToolbarLayout mCollapsingToolbarLayout;
    private FloatingActionButton mFloatingActionButton;

    private Contact mContact;

    private LayoutGroup mPhoneGroup;
    private LayoutGroup mNameGroup;
    private LayoutGroup mNicknameGroup;
    private LayoutGroup mEmailGroup;
    private LayoutGroup mAddressGroup;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contact);

        mToolbar = findViewById(R.id.toolbar);
        mCollapsingToolbarLayout = findViewById(R.id.toolbar_layout);
        mFloatingActionButton = findViewById(R.id.floatingActionButton);

        mPhoneGroup = new LayoutGroup(R.id.phoneLayout, R.id.phone);
        mNameGroup = new LayoutGroup(R.id.nameLayout, R.id.name);
        mNicknameGroup = new LayoutGroup(R.id.nicknameLayout, R.id.nickname);
        mEmailGroup = new LayoutGroup(R.id.emailLayout, R.id.email);
        mAddressGroup = new LayoutGroup(R.id.addressLayout, R.id.address);

        mContact = (Contact) getIntent().getSerializableExtra(KEY_CONTACT);
        if (mContact == null) {
            finish();
            return;
        }

        boolean messageButton = getIntent().getBooleanExtra(KEY_MESSAGE_BUTTON, true);

        setSupportActionBar(mToolbar);
        ActionBarColorUtil.apply(this, mCollapsingToolbarLayout);

        String title = mContact.getDisplayableTitle();
        mToolbar.setTitle(title);
        mCollapsingToolbarLayout.setTitle(title);

        if (messageButton) {
            mFloatingActionButton.show();
        } else {
            mFloatingActionButton.hide();
        }

        mFloatingActionButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MessagesActivity.start(ContactActivity.this, REQUEST_CODE_CONTACT_EDITOR, mContact);
            }
        });

        updateGroups();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_contact, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_edit: {
                ContactEditorActivity.start(this, REQUEST_CODE_CONTACT_EDITOR, mContact);

                return true;
            }
        }

        return super.onOptionsItemSelected(item);
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

    public void updateGroups() {
        mPhoneGroup.update(mContact.getPhone());
        mNameGroup.update(mContact.getName());
        mNicknameGroup.update(mContact.getNickname());
        mEmailGroup.update(mContact.getEmail());
        mAddressGroup.update(mContact.getAddress());
    }

    public static void start(Activity context, int requestCode, Contact contact, boolean messageButton) {
        Intent intent = new Intent(context, ContactActivity.class);
        intent.putExtra(KEY_CONTACT, contact);
        intent.putExtra(KEY_MESSAGE_BUTTON, messageButton);

        context.startActivityForResult(intent, requestCode);
    }

    private class LayoutGroup {

        private final TextInputLayout mTextInputLayout;
        private final TextInputEditText mTextInputEditText;

        public LayoutGroup(int textInputLayoutId, int textInputEditTextId) {
            this.mTextInputLayout = findViewById(textInputLayoutId);
            this.mTextInputEditText = findViewById(textInputEditTextId);
        }

        public void update(String value) {
            boolean valid = TextUtils.isEmpty(value);

            mTextInputLayout.setVisibility(valid ? View.GONE : View.VISIBLE);
            mTextInputEditText.setText(valid ? null : value);
        }
    }
}