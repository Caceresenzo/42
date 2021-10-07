package ft.hangouts.activity;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.textfield.TextInputEditText;

import java.util.function.BiConsumer;
import java.util.function.Consumer;

import ft.hangouts.R;
import ft.hangouts.helper.DatabaseHelper;
import ft.hangouts.model.Contact;
import ft.hangouts.util.ActionBarColorUtil;

public class ContactEditorActivity extends AppCompatActivity {

    public static final String KEY_CONTACT = "contact";

    private TextInputEditText mPhoneInput;
    private TextInputEditText mNameInput;
    private TextInputEditText mNicknameInput;
    private TextInputEditText mEmailInput;
    private TextInputEditText mAddressInput;
    private FloatingActionButton mFloatingActionButton;

    private Contact mContact;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contact_edit);

        ActionBarColorUtil.apply(this);

        mPhoneInput = findViewById(R.id.phone);
        mNameInput = findViewById(R.id.name);
        mNicknameInput = findViewById(R.id.nickname);
        mEmailInput = findViewById(R.id.email);
        mAddressInput = findViewById(R.id.address);
        mFloatingActionButton = findViewById(R.id.floatingActionButton);

        mContact = (Contact) getIntent().getSerializableExtra(KEY_CONTACT);
        if (mContact == null) {
            mContact = new Contact();

            getSupportActionBar().setTitle("New contact");
        } else {
            mPhoneInput.setText(mContact.getPhone());
            mNameInput.setText(mContact.getName());
            mNicknameInput.setText(mContact.getNickname());
            mEmailInput.setText(mContact.getEmail());
            mAddressInput.setText(mContact.getAddress());

            getSupportActionBar().setTitle(String.format("Contact: %s", mContact.getPhone()));
        }

        new ContactTextWatch(mPhoneInput, Contact.Columns.COLUMN_NAME_PHONE);
        new ContactTextWatch(mNameInput, Contact.Columns.COLUMN_NAME_NAME);
        new ContactTextWatch(mNicknameInput, Contact.Columns.COLUMN_NAME_NICKNAME);
        new ContactTextWatch(mEmailInput, Contact.Columns.COLUMN_NAME_EMAIL);
        new ContactTextWatch(mAddressInput, Contact.Columns.COLUMN_NAME_ADDRESS);

        mFloatingActionButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                save();
            }
        });
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

    public void save() {
        new DatabaseHelper(this).save(mContact);

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

        private final TextInputEditText mInput;
        private final String mField;

        public ContactTextWatch(TextInputEditText input, String field) {
            mInput = input;
            mField = field;

            mInput.addTextChangedListener(this);
        }

        @Override
        public void afterTextChanged(Editable s) {}

        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {}

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
        }

    }

}