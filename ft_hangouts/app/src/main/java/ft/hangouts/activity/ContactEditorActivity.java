package ft.hangouts.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextUtils;
import android.text.TextWatcher;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import ft.hangouts.Constants;
import ft.hangouts.R;
import ft.hangouts.activity.base.TrackedActivity;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.util.ActionBarColorUtil;

public class ContactEditorActivity extends TrackedActivity {

    public static final String KEY_CONTACT = "contact";

    private EditText mPhoneInput;
    private EditText mNameInput;
    private EditText mNicknameInput;
    private EditText mEmailInput;
    private EditText mAddressInput;
    private Button mSaveButton;

    private Contact mContact;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contact_editor);

        ActionBarColorUtil.apply(this);

        mPhoneInput = findViewById(R.id.phone);
        mNameInput = findViewById(R.id.name);
        mNicknameInput = findViewById(R.id.nickname);
        mEmailInput = findViewById(R.id.email);
        mAddressInput = findViewById(R.id.address);
        mSaveButton = findViewById(R.id.save);

        mContact = (Contact) getIntent().getSerializableExtra(KEY_CONTACT);
        if (mContact == null) {
            mContact = new Contact();

            getActionBar().setTitle(R.string.contact_new);
        } else {
            mPhoneInput.setText(mContact.getPhone());
            mNameInput.setText(mContact.getName());
            mNicknameInput.setText(mContact.getNickname());
            mEmailInput.setText(mContact.getEmail());
            mAddressInput.setText(mContact.getAddress());

            getActionBar().setTitle(mContact.getDisplayableTitle());
        }

        getActionBar().setDisplayHomeAsUpEnabled(true);

        new ContactTextWatch(mPhoneInput, Contact.Columns.COLUMN_NAME_PHONE, true);
        new ContactTextWatch(mNameInput, Contact.Columns.COLUMN_NAME_NAME);
        new ContactTextWatch(mNicknameInput, Contact.Columns.COLUMN_NAME_NICKNAME);
        new ContactTextWatch(mEmailInput, Contact.Columns.COLUMN_NAME_EMAIL);
        new ContactTextWatch(mAddressInput, Contact.Columns.COLUMN_NAME_ADDRESS);

        mSaveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                save();
            }
        });

        mSaveButton.setEnabled(!TextUtils.isEmpty(mContact.getPhone()));
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);

        outState.putSerializable(KEY_CONTACT, mContact);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        mContact = (Contact) savedInstanceState.getSerializable(KEY_CONTACT);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (!isNew()) {
            getMenuInflater().inflate(R.menu.menu_contact_editor, menu);
        }

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home: {
                finish();

                return true;
            }

            case R.id.action_delete: {
                DatabaseHelper helper = new DatabaseHelper(this);

                helper.deleteAllMessageByContact(mContact);
                helper.delete(mContact);

                Intent intent = new Intent();
                intent.putExtra(Constants.KEY_CONTACT, mContact);

                setResult(Constants.RESULT_CODE_REMOVED, intent);
                finish();

                return true;
            }
        }

        return super.onOptionsItemSelected(item);
    }

    public void save() {
        new DatabaseHelper(this).save(mContact);

        Intent intent = new Intent();
        intent.putExtra(Constants.KEY_CONTACT, mContact);

        setResult(Constants.RESULT_CODE_EDITED, intent);
        finish();
    }

    public boolean isNew() {
        return mContact.getId() == 0;
    }

    public static void start(Activity context, int requestCode, Contact contact) {
        Intent intent = new Intent(context, ContactEditorActivity.class);
        intent.putExtra(ContactEditorActivity.KEY_CONTACT, contact);

        context.startActivityForResult(intent, requestCode);
    }

    public class ContactTextWatch implements TextWatcher {

        private final EditText mInput;
        private final String mField;
        private final boolean mDisableSave;

        public ContactTextWatch(EditText input, String field) {
            this(input, field, false);
        }

        public ContactTextWatch(EditText input, String field, boolean disableSave) {
            mInput = input;
            mField = field;
            mDisableSave = disableSave;

            mInput.addTextChangedListener(this);
        }

        @Override
        public void afterTextChanged(Editable s) {
        }

        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {
        }

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {
            String value = s.toString();

            switch (mField) {
                case Contact.Columns.COLUMN_NAME_PHONE: {
                    mContact.setPhone(value);
                    break;
                }

                case Contact.Columns.COLUMN_NAME_NAME: {
                    mContact.setName(value);
                    break;
                }

                case Contact.Columns.COLUMN_NAME_NICKNAME: {
                    mContact.setNickname(value);
                    break;
                }

                case Contact.Columns.COLUMN_NAME_EMAIL: {
                    mContact.setEmail(value);
                    break;
                }

                case Contact.Columns.COLUMN_NAME_ADDRESS: {
                    mContact.setAddress(value);
                    break;
                }
            }

            if (mDisableSave) {
                mSaveButton.setEnabled(!value.isEmpty());
            }
        }

    }

}